#include <GL/glew.h>
#include <stdio.h>
#include <math.h>

#include <GLFW/glfw3.h>

#include <toolcl/vec3.h>
#include <toolcl/mat4.h>

static const char *vertex_shader_source =
    "#version 330 core\n"
    "\n"
    "layout (location = 0) in vec3 a_position;\n"
    "layout (location = 1) in vec3 a_normal;\n"
    "\n"
    "uniform mat4 u_mvp;\n"
    "uniform mat4 u_model;\n"
    "\n"
    "out vec3 v_normal;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = u_mvp * vec4(a_position, 1.0);\n"
    "    v_normal = mat3(u_model) * a_normal;\n"
    "}\n";

static const char *fragment_shader_source =
    "#version 330 core\n"
    "\n"
    "in vec3 v_normal;\n"
    "\n"
    "uniform vec3 u_light_direction;\n"
    "uniform vec3 u_base_color;\n"
    "\n"
    "out vec4 frag_color;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec3 normal = normalize(v_normal);\n"
    "    vec3 light = normalize(-u_light_direction);\n"
    "\n"
    "    float diffuse = max(dot(normal, light), 0.0);\n"
    "    float ambient = 0.20;\n"
    "    float lighting = ambient + diffuse * 0.80;\n"
    "\n"
    "    frag_color = vec4(u_base_color * lighting, 1.0);\n"
    "}\n";

static GLuint compile_shader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char log[1024];
        glGetShaderInfoLog(shader, sizeof(log), NULL, log);
        fprintf(stderr, "Shader compilation failed:\n%s\n", log);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

static GLuint create_shader_program(void)
{
    GLuint vertex_shader =
        compile_shader(GL_VERTEX_SHADER, vertex_shader_source);

    GLuint fragment_shader =
        compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);

    if (!vertex_shader || !fragment_shader) {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return 0;
    }

    GLuint program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    GLint success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        char log[1024];
        glGetProgramInfoLog(program, sizeof(log), NULL, log);
        fprintf(stderr, "Shader linking failed:\n%s\n", log);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        glDeleteProgram(program);

        return 0;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

int main(void)
{
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW.\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window =
        glfwCreateWindow(800, 600, "ToolCL - Hello 3D Lighting", NULL, NULL);

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

    /*
     * Lighting variant intentionally leaves VSync disabled.
     * hello_3d_vsync demonstrates glfwSwapInterval(1).
     */
    glfwSwapInterval(0);

    glEnable(GL_DEPTH_TEST);

    GLuint program = create_shader_program();

    if (!program) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    /*
     * Cube vertices:
     * position (x, y, z) + normal (x, y, z)
     *
     * Each face has its own normal so the cube receives
     * proper flat directional lighting.
     */
    const float vertices[] = {
        /* Front */
        -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,

         0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,

        /* Back */
         0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,

        -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,

        /* Left */
        -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,

        /* Right */
         0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,

         0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,

        /* Top */
        -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,   0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   0.0f,  1.0f, 0.0f,

         0.5f,  0.5f, -0.5f,   0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   0.0f,  1.0f, 0.0f,

        /* Bottom */
        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,

         0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f
    };

    GLuint vao;
    GLuint vbo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
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

    GLint mvp_location =
        glGetUniformLocation(program, "u_mvp");

    GLint model_location =
        glGetUniformLocation(program, "u_model");

    GLint light_location =
        glGetUniformLocation(program, "u_light_direction");

    GLint color_location =
        glGetUniformLocation(program, "u_base_color");

    while (!glfwWindowShouldClose(window)) {
        int width;
        int height;

        glfwGetFramebufferSize(window, &width, &height);

        if (height == 0)
            height = 1;

        glViewport(0, 0, width, height);

        glClearColor(0.04f, 0.04f, 0.06f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time = (float)glfwGetTime();

        ToolCL_Mat4 model =
            toolcl_mat4_mul(
                toolcl_mat4_rotate_y(time),
                toolcl_mat4_rotate_x(time * 0.65f)
            );

        model =
            toolcl_mat4_mul(
                model,
                toolcl_mat4_rotate_z(time * 0.35f)
            );

        ToolCL_Mat4 view =
            toolcl_mat4_translate(0.0f, 0.0f, -2.5f);

        ToolCL_Mat4 projection =
            toolcl_mat4_perspective(
                45.0f * 3.14159265358979323846f / 180.0f,
                (float)width / (float)height,
                0.1f,
                100.0f
            );

        ToolCL_Mat4 view_model =
            toolcl_mat4_mul(view, model);

        ToolCL_Mat4 mvp =
            toolcl_mat4_mul(projection, view_model);

        ToolCL_Vec3 light_direction =
            toolcl_vec3_normalize(
                toolcl_vec3(-1.0f, -1.0f, -1.0f)
            );

        ToolCL_Vec3 base_color =
            toolcl_vec3(0.25f, 0.65f, 1.0f);

        glUseProgram(program);

        glUniformMatrix4fv(
            mvp_location,
            1,
            GL_FALSE,
            mvp.m
        );

        glUniformMatrix4fv(
            model_location,
            1,
            GL_FALSE,
            model.m
        );

        glUniform3f(
            light_location,
            light_direction.x,
            light_direction.y,
            light_direction.z
        );

        glUniform3f(
            color_location,
            base_color.x,
            base_color.y,
            base_color.z
        );

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
