#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

#include <toolcl/vec3.h>
#include <toolcl/mat4.h>

static const char *shadow_vertex_shader =
    "#version 330 core\n"
    "layout (location = 0) in vec3 a_position;\n"
    "uniform mat4 u_light_space;\n"
    "uniform mat4 u_model;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = u_light_space * u_model * vec4(a_position, 1.0);\n"
    "}\n";

static const char *shadow_fragment_shader =
    "#version 330 core\n"
    "void main()\n"
    "{\n"
    "}\n";

static const char *scene_vertex_shader =
    "#version 330 core\n"
    "layout (location = 0) in vec3 a_position;\n"
    "layout (location = 1) in vec3 a_normal;\n"
    "uniform mat4 u_mvp;\n"
    "uniform mat4 u_model;\n"
    "uniform mat4 u_light_space;\n"
    "out vec3 v_position;\n"
    "out vec3 v_normal;\n"
    "out vec4 v_light_position;\n"
    "void main()\n"
    "{\n"
    "    vec4 world_position = u_model * vec4(a_position, 1.0);\n"
    "    gl_Position = u_mvp * vec4(a_position, 1.0);\n"
    "    v_position = world_position.xyz;\n"
    "    v_normal = mat3(u_model) * a_normal;\n"
    "    v_light_position = u_light_space * world_position;\n"
    "}\n";

static const char *scene_fragment_shader =
    "#version 330 core\n"
    "in vec3 v_position;\n"
    "in vec3 v_normal;\n"
    "in vec4 v_light_position;\n"
    "uniform sampler2D u_shadow_map;\n"
    "uniform vec3 u_light_direction;\n"
    "uniform vec3 u_base_color;\n"
    "uniform vec3 u_view_position;\n"
    "out vec4 frag_color;\n"
    "float get_shadow(vec4 light_position, vec3 normal, vec3 light)\n"
    "{\n"
    "    vec3 projected = light_position.xyz / light_position.w;\n"
    "    projected = projected * 0.5 + 0.5;\n"
    "    if (projected.z > 1.0 || projected.x < 0.0 || projected.x > 1.0 || projected.y < 0.0 || projected.y > 1.0)\n"
    "        return 0.0;\n"
    "    float bias = max(0.004 * (1.0 - dot(normal, light)), 0.001);\n"
    "    vec2 texel = 1.0 / textureSize(u_shadow_map, 0);\n"
    "    float shadow = 0.0;\n"
    "    for (int x = -1; x <= 1; ++x)\n"
    "    {\n"
    "        for (int y = -1; y <= 1; ++y)\n"
    "        {\n"
    "            float depth = texture(u_shadow_map, projected.xy + vec2(x, y) * texel).r;\n"
    "            shadow += projected.z - bias > depth ? 1.0 : 0.0;\n"
    "        }\n"
    "    }\n"
    "    return shadow / 9.0;\n"
    "}\n"
    "void main()\n"
    "{\n"
    "    vec3 normal = normalize(v_normal);\n"
    "    vec3 light = normalize(-u_light_direction);\n"
    "    vec3 view = normalize(u_view_position - v_position);\n"
    "    vec3 half_vector = normalize(light + view);\n"
    "    float diffuse = max(dot(normal, light), 0.0);\n"
    "    float specular = pow(max(dot(normal, half_vector), 0.0), 32.0);\n"
    "    float shadow = get_shadow(v_light_position, normal, light);\n"
    "    float ambient = 0.12;\n"
    "    float direct = diffuse * 0.78 * (1.0 - shadow * 0.88);\n"
    "    float highlight = specular * 0.18 * (1.0 - shadow);\n"
    "    vec3 color = u_base_color * (ambient + direct);\n"
    "    color += vec3(1.0) * highlight;\n"
    "    frag_color = vec4(color, 1.0);\n"
    "}\n";

static GLuint compile_shader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    GLint success = 0;
    char log[1024];

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, sizeof(log), NULL, log);
        fprintf(stderr, "Shader compilation failed:\n%s\n", log);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

static GLuint create_program(const char *vertex_source, const char *fragment_source)
{
    GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_source);
    GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_source);
    GLuint program;
    GLint success = 0;
    char log[1024];

    if (!vertex_shader || !fragment_shader) {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return 0;
    }

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    if (!success) {
        glGetProgramInfoLog(program, sizeof(log), NULL, log);
        fprintf(stderr, "Shader linking failed:\n%s\n", log);
        glDeleteProgram(program);
        return 0;
    }

    return program;
}

static ToolCL_Mat4 make_ortho(
    float left,
    float right,
    float bottom,
    float top,
    float near_plane,
    float far_plane
)
{
    ToolCL_Mat4 matrix = toolcl_mat4_zero();

    matrix.data[0] = 2.0f / (right - left);
    matrix.data[5] = 2.0f / (top - bottom);
    matrix.data[10] = -2.0f / (far_plane - near_plane);
    matrix.data[12] = -(right + left) / (right - left);
    matrix.data[13] = -(top + bottom) / (top - bottom);
    matrix.data[14] = -(far_plane + near_plane) / (far_plane - near_plane);
    matrix.data[15] = 1.0f;

    return matrix;
}

static ToolCL_Mat4 make_look_at(
    ToolCL_Vec3 eye,
    ToolCL_Vec3 center,
    ToolCL_Vec3 up
)
{
    ToolCL_Vec3 forward =
        toolcl_vec3_normalize(
            toolcl_vec3_sub(center, eye)
        );

    ToolCL_Vec3 side =
        toolcl_vec3_normalize(
            toolcl_vec3_cross(forward, up)
        );

    ToolCL_Vec3 real_up =
        toolcl_vec3_cross(side, forward);

    ToolCL_Mat4 matrix = toolcl_mat4_identity();

    matrix.data[0] = side.x;
    matrix.data[1] = real_up.x;
    matrix.data[2] = -forward.x;

    matrix.data[4] = side.y;
    matrix.data[5] = real_up.y;
    matrix.data[6] = -forward.y;

    matrix.data[8] = side.z;
    matrix.data[9] = real_up.z;
    matrix.data[10] = -forward.z;

    matrix.data[12] = -toolcl_vec3_dot(side, eye);
    matrix.data[13] = -toolcl_vec3_dot(real_up, eye);
    matrix.data[14] = toolcl_vec3_dot(forward, eye);

    return matrix;
}

int main(void)
{
    const float cube_vertices[] = {
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,

         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f
    };

    const float plane_vertices[] = {
        -4.0f, 0.0f, -4.0f, 0.0f, 1.0f, 0.0f,
         4.0f, 0.0f, -4.0f, 0.0f, 1.0f, 0.0f,
         4.0f, 0.0f,  4.0f, 0.0f, 1.0f, 0.0f,
         4.0f, 0.0f,  4.0f, 0.0f, 1.0f, 0.0f,
        -4.0f, 0.0f,  4.0f, 0.0f, 1.0f, 0.0f,
        -4.0f, 0.0f, -4.0f, 0.0f, 1.0f, 0.0f
    };

    const int shadow_size = 1024;
    GLFWwindow *window;
    GLuint scene_program;
    GLuint shadow_program;
    GLuint cube_vao;
    GLuint cube_vbo;
    GLuint plane_vao;
    GLuint plane_vbo;
    GLuint shadow_fbo;
    GLuint shadow_texture;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW.\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(
        800,
        600,
        "ToolCL - Hello 3D Lighting VSync",
        NULL,
        NULL
    );

    if (!window) {
        fprintf(stderr, "Failed to create GLFW window.\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW.\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);

    scene_program =
        create_program(scene_vertex_shader, scene_fragment_shader);

    shadow_program =
        create_program(shadow_vertex_shader, shadow_fragment_shader);

    if (!scene_program || !shadow_program) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    glGenVertexArrays(1, &cube_vao);
    glGenBuffers(1, &cube_vbo);

    glBindVertexArray(cube_vao);
    glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(cube_vertices),
        cube_vertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void *)0
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void *)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &plane_vao);
    glGenBuffers(1, &plane_vbo);

    glBindVertexArray(plane_vao);
    glBindBuffer(GL_ARRAY_BUFFER, plane_vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(plane_vertices),
        plane_vertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void *)0
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void *)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glGenFramebuffers(1, &shadow_fbo);
    glGenTextures(1, &shadow_texture);

    glBindTexture(GL_TEXTURE_2D, shadow_texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_DEPTH_COMPONENT24,
        shadow_size,
        shadow_size,
        0,
        GL_DEPTH_COMPONENT,
        GL_FLOAT,
        NULL
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    {
        const float border[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(
            GL_TEXTURE_2D,
            GL_TEXTURE_BORDER_COLOR,
            border
        );
    }

    glBindFramebuffer(GL_FRAMEBUFFER, shadow_fbo);
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,
        GL_TEXTURE_2D,
        shadow_texture,
        0
    );
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr, "Failed to create shadow framebuffer.\n");
        glDeleteTextures(1, &shadow_texture);
        glDeleteFramebuffers(1, &shadow_fbo);
        glDeleteProgram(scene_program);
        glDeleteProgram(shadow_program);
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    GLint scene_mvp_location =
        glGetUniformLocation(scene_program, "u_mvp");

    GLint scene_model_location =
        glGetUniformLocation(scene_program, "u_model");

    GLint scene_light_space_location =
        glGetUniformLocation(scene_program, "u_light_space");

    GLint scene_light_location =
        glGetUniformLocation(scene_program, "u_light_direction");

    GLint scene_color_location =
        glGetUniformLocation(scene_program, "u_base_color");

    GLint scene_view_location =
        glGetUniformLocation(scene_program, "u_view_position");

    GLint scene_shadow_location =
        glGetUniformLocation(scene_program, "u_shadow_map");

    GLint shadow_light_space_location =
        glGetUniformLocation(shadow_program, "u_light_space");

    GLint shadow_model_location =
        glGetUniformLocation(shadow_program, "u_model");

    ToolCL_Vec3 light_direction =
        toolcl_vec3_normalize(
            toolcl_vec3(-0.6f, -1.0f, -0.8f)
        );

    ToolCL_Vec3 light_position =
        toolcl_vec3(3.5f, 5.0f, 4.0f);

    while (!glfwWindowShouldClose(window)) {
        int width;
        int height;
        float time;
        ToolCL_Mat4 rotation;
        ToolCL_Mat4 model;
        ToolCL_Mat4 view;
        ToolCL_Mat4 projection;
        ToolCL_Mat4 mvp;
        ToolCL_Mat4 light_view;
        ToolCL_Mat4 light_projection;
        ToolCL_Mat4 light_space;
        ToolCL_Mat4 plane_model;
        ToolCL_Mat4 plane_mvp;

        glfwGetFramebufferSize(window, &width, &height);

        if (height == 0)
            height = 1;

        time = (float)glfwGetTime();

        rotation =
            toolcl_mat4_mul(
                toolcl_mat4_rotate_y(time),
                toolcl_mat4_mul(
                    toolcl_mat4_rotate_x(time * 0.65f),
                    toolcl_mat4_rotate_z(time * 0.35f)
                )
            );

        model =
            toolcl_mat4_mul(
                toolcl_mat4_translate(
                    toolcl_vec3(0.0f, 0.5f, 0.0f)
                ),
                rotation
            );

        view =
            toolcl_mat4_translate(
                toolcl_vec3(0.0f, -0.25f, -3.2f)
            );

        projection =
            toolcl_mat4_perspective(
                (45.0f * 3.14159265358979323846f / 180.0f),
                (float)width / (float)height,
                0.1f,
                100.0f
            );

        mvp =
            toolcl_mat4_mul(
                projection,
                toolcl_mat4_mul(view, model)
            );

        light_view =
            make_look_at(
                light_position,
                toolcl_vec3(0.0f, 0.0f, 0.0f),
                toolcl_vec3(0.0f, 1.0f, 0.0f)
            );

        light_projection =
            make_ortho(
                -5.0f,
                5.0f,
                -5.0f,
                5.0f,
                0.5f,
                15.0f
            );

        light_space =
            toolcl_mat4_mul(
                light_projection,
                light_view
            );

        plane_model = toolcl_mat4_identity();

        plane_mvp =
            toolcl_mat4_mul(
                projection,
                toolcl_mat4_mul(view, plane_model)
            );

        glViewport(0, 0, shadow_size, shadow_size);
        glBindFramebuffer(GL_FRAMEBUFFER, shadow_fbo);
        glClear(GL_DEPTH_BUFFER_BIT);

        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(2.0f, 4.0f);

        glUseProgram(shadow_program);

        glUniformMatrix4fv(
            shadow_light_space_location,
            1,
            GL_FALSE,
            light_space.data
        );

        glUniformMatrix4fv(
            shadow_model_location,
            1,
            GL_FALSE,
            model.data
        );

        glBindVertexArray(cube_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glUniformMatrix4fv(
            shadow_model_location,
            1,
            GL_FALSE,
            plane_model.data
        );

        glBindVertexArray(plane_vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisable(GL_POLYGON_OFFSET_FILL);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glViewport(0, 0, width, height);
        glClearColor(0.025f, 0.035f, 0.055f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(scene_program);

        glUniformMatrix4fv(
            scene_light_space_location,
            1,
            GL_FALSE,
            light_space.data
        );

        glUniform3f(
            scene_light_location,
            light_direction.x,
            light_direction.y,
            light_direction.z
        );

        glUniform3f(
            scene_view_location,
            0.0f,
            0.25f,
            3.2f
        );

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, shadow_texture);

        glUniform1i(
            scene_shadow_location,
            0
        );

        glBindVertexArray(plane_vao);

        glUniformMatrix4fv(
            scene_mvp_location,
            1,
            GL_FALSE,
            plane_mvp.data
        );

        glUniformMatrix4fv(
            scene_model_location,
            1,
            GL_FALSE,
            plane_model.data
        );

        glUniform3f(
            scene_color_location,
            0.08f,
            0.10f,
            0.14f
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(cube_vao);

        glUniformMatrix4fv(
            scene_mvp_location,
            1,
            GL_FALSE,
            mvp.data
        );

        glUniformMatrix4fv(
            scene_model_location,
            1,
            GL_FALSE,
            model.data
        );

        glUniform3f(
            scene_color_location,
            0.18f,
            0.55f,
            1.0f
        );

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteTextures(1, &shadow_texture);
    glDeleteFramebuffers(1, &shadow_fbo);
    glDeleteBuffers(1, &cube_vbo);
    glDeleteVertexArrays(1, &cube_vao);
    glDeleteBuffers(1, &plane_vbo);
    glDeleteVertexArrays(1, &plane_vao);
    glDeleteProgram(scene_program);
    glDeleteProgram(shadow_program);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
