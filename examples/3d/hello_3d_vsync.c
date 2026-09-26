#include <stdio.h>
#include <stdlib.h>

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#include <toolcl/mat4.h>
#include <toolcl/vec3.h>

static const char *vertex_shader_source =
    "#version 330 core\n"
    "layout (location = 0) in vec3 a_position;\n"
    "layout (location = 1) in vec3 a_color;\n"
    "layout (location = 2) in vec3 a_normal;\n"
    "uniform mat4 u_mvp;\n"
    "uniform mat4 u_model;\n"
    "uniform vec3 u_light_direction;\n"
    "out vec3 v_color;\n"
    "out vec3 v_normal;\n"
    "void main() {\n"
    "    gl_Position = u_mvp * vec4(a_position, 1.0);\n"
    "    v_color = a_color;\n"
    "    v_normal = mat3(u_model) * a_normal;\n"
    "}\n";

static const char *fragment_shader_source =
    "#version 330 core\n"
    "in vec3 v_color;\n"
    "in vec3 v_normal;\n"
    "uniform vec3 u_light_direction;\n"
    "out vec4 frag_color;\n"
    "void main() {\n"
    "    vec3 normal = normalize(v_normal);\n"
    "    vec3 light = normalize(-u_light_direction);\n"
    "    float diffuse = max(dot(normal, light), 0.0);\n"
    "    float lighting = 0.25 + diffuse * 0.75;\n"
    "    frag_color = vec4(v_color * lighting, 1.0);\n"
    "}\n";

static void print_shader_log(GLuint shader)
{
    char log[1024];
    GLsizei length = 0;

    glGetShaderInfoLog(shader, sizeof(log), &length, log);

    if (length > 0)
        fprintf(stderr, "Shader error: %.*s\n", (int)length, log);
}

static void print_program_log(GLuint program)
{
    char log[1024];
    GLsizei length = 0;

    glGetProgramInfoLog(program, sizeof(log), &length, log);

    if (length > 0)
        fprintf(stderr, "Program error: %.*s\n", (int)length, log);
}

static GLuint compile_shader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    GLint success = GL_FALSE;

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        print_shader_log(shader);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

static GLuint create_program(void)
{
    GLuint vertex_shader =
        compile_shader(GL_VERTEX_SHADER, vertex_shader_source);

    GLuint fragment_shader =
        compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);

    if (vertex_shader == 0 || fragment_shader == 0) {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return 0;
    }

    GLuint program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    GLint success = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        print_program_log(program);
        glDeleteProgram(program);
        return 0;
    }

    return program;
}

static ToolCL_Mat4 make_look_at(
    ToolCL_Vec3 eye,
    ToolCL_Vec3 target,
    ToolCL_Vec3 up
)
{
    ToolCL_Vec3 forward =
        toolcl_vec3_normalize(
            toolcl_vec3_sub(target, eye)
        );

    ToolCL_Vec3 right =
        toolcl_vec3_normalize(
            toolcl_vec3_cross(forward, up)
        );

    ToolCL_Vec3 corrected_up =
        toolcl_vec3_cross(right, forward);

    ToolCL_Mat4 view = toolcl_mat4_identity();

    view.data[0] = right.x;
    view.data[1] = right.y;
    view.data[2] = right.z;

    view.data[4] = corrected_up.x;
    view.data[5] = corrected_up.y;
    view.data[6] = corrected_up.z;

    view.data[8] = -forward.x;
    view.data[9] = -forward.y;
    view.data[10] = -forward.z;

    view.data[12] = -toolcl_vec3_dot(right, eye);
    view.data[13] = -toolcl_vec3_dot(corrected_up, eye);
    view.data[14] = toolcl_vec3_dot(forward, eye);

    return view;
}

static void framebuffer_size_callback(
    GLFWwindow *window,
    int width,
    int height
)
{
    (void)window;

    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);
}

int main(void)
{
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW.\n");
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window =
        glfwCreateWindow(800, 600, "ToolCL - Hello 3D VSync", NULL, NULL);

    if (!window) {
        fprintf(stderr, "Failed to create OpenGL window.\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(
        window,
        framebuffer_size_callback
    );

    glEnable(GL_DEPTH_TEST);

    static const float cube_vertices[] = {
        -0.5f,-0.5f, 0.5f, 1,0,0, 0,0,1,
         0.5f,-0.5f, 0.5f, 0,1,0, 0,0,1,
         0.5f, 0.5f, 0.5f, 0,0,1, 0,0,1,
         0.5f, 0.5f, 0.5f, 0,0,1, 0,0,1,
        -0.5f, 0.5f, 0.5f, 1,1,0, 0,0,1,
        -0.5f,-0.5f, 0.5f, 1,0,0, 0,0,1,

         0.5f,-0.5f,-0.5f, 0,1,1, 0,0,-1,
        -0.5f,-0.5f,-0.5f, 1,0,1, 0,0,-1,
        -0.5f, 0.5f,-0.5f, 1,1,1, 0,0,-1,
        -0.5f, 0.5f,-0.5f, 1,1,1, 0,0,-1,
         0.5f, 0.5f,-0.5f, .5,.5,.5, 0,0,-1,
         0.5f,-0.5f,-0.5f, 0,1,1, 0,0,-1,

        -0.5f,-0.5f,-0.5f, 1,0,1, -1,0,0,
        -0.5f,-0.5f, 0.5f, 1,0,0, -1,0,0,
        -0.5f, 0.5f, 0.5f, 0,1,0, -1,0,0,
        -0.5f, 0.5f, 0.5f, 0,1,0, -1,0,0,
        -0.5f, 0.5f,-0.5f, 1,1,1, -1,0,0,
        -0.5f,-0.5f,-0.5f, 1,0,1, -1,0,0,

         0.5f,-0.5f, 0.5f, 0,1,0, 1,0,0,
         0.5f,-0.5f,-0.5f, 0,1,1, 1,0,0,
         0.5f, 0.5f,-0.5f, .5,.5,.5, 1,0,0,
         0.5f, 0.5f,-0.5f, .5,.5,.5, 1,0,0,
         0.5f, 0.5f, 0.5f, 0,0,1, 1,0,0,
         0.5f,-0.5f, 0.5f, 0,1,0, 1,0,0,

        -0.5f, 0.5f, 0.5f, 0,1,0, 0,1,0,
         0.5f, 0.5f, 0.5f, 0,0,1, 0,1,0,
         0.5f, 0.5f,-0.5f, .5,.5,.5, 0,1,0,
         0.5f, 0.5f,-0.5f, .5,.5,.5, 0,1,0,
        -0.5f, 0.5f,-0.5f, 1,1,1, 0,1,0,
        -0.5f, 0.5f, 0.5f, 0,1,0, 0,1,0,

        -0.5f,-0.5f,-0.5f, 1,0,1, 0,-1,0,
         0.5f,-0.5f,-0.5f, 0,1,1, 0,-1,0,
         0.5f,-0.5f, 0.5f, 0,1,0, 0,-1,0,
         0.5f,-0.5f, 0.5f, 0,1,0, 0,-1,0,
        -0.5f,-0.5f, 0.5f, 1,0,0, 0,-1,0,
        -0.5f,-0.5f,-0.5f, 1,0,1, 0,-1,0
    };

    GLuint vao = 0;
    GLuint vbo = 0;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(cube_vertices),
        cube_vertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        9 * sizeof(float),
        (void *)0
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        9 * sizeof(float),
        (void *)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(
        2, 3, GL_FLOAT, GL_FALSE,
        9 * sizeof(float),
        (void *)(6 * sizeof(float))
    );
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint program = create_program();

    if (program == 0) {
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    GLint mvp_location =
        glGetUniformLocation(program, "u_mvp");

    GLint model_location =
        glGetUniformLocation(program, "u_model");

    GLint light_direction_location =
        glGetUniformLocation(program, "u_light_direction");

    ToolCL_Vec3 light_direction =
        toolcl_vec3(-0.6f, -1.0f, -0.8f);

    while (!glfwWindowShouldClose(window)) {
        int width;
        int height;

        glfwGetFramebufferSize(window, &width, &height);

        if (height == 0)
            height = 1;

        float aspect =
            (float)width / (float)height;

        float time =
            (float)glfwGetTime();

        ToolCL_Mat4 rotation =
            toolcl_mat4_mul(
                toolcl_mat4_rotate_y(time),
                toolcl_mat4_rotate_x(time * 0.7f)
            );

        rotation =
            toolcl_mat4_mul(
                rotation,
                toolcl_mat4_rotate_z(time * 0.35f)
            );

        ToolCL_Mat4 model =
            toolcl_mat4_mul(
                toolcl_mat4_translate(
                    toolcl_vec3(0.0f, 0.0f, 0.0f)
                ),
                rotation
            );

        ToolCL_Mat4 view =
            make_look_at(
                toolcl_vec3(0.0f, 1.35f, 3.4f),
                toolcl_vec3(0.0f, 0.0f, 0.0f),
                toolcl_vec3(0.0f, 1.0f, 0.0f)
            );

        ToolCL_Mat4 projection =
            toolcl_mat4_perspective(
                (45.0f * 3.14159265358979323846f / 180.0f),
                aspect,
                0.1f,
                100.0f
            );

        ToolCL_Mat4 mvp =
            toolcl_mat4_mul(
                projection,
                toolcl_mat4_mul(view, model)
            );

        glViewport(0, 0, width, height);

        glClearColor(
            0.04f, 0.04f, 0.06f, 1.0f
        );

        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );

        glUseProgram(program);

        glUniformMatrix4fv(
            mvp_location,
            1,
            GL_FALSE,
            mvp.data
        );

        glUniformMatrix4fv(
            model_location,
            1,
            GL_FALSE,
            model.data
        );

        glUniform3f(
            light_direction_location,
            light_direction.x,
            light_direction.y,
            light_direction.z
        );

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(program);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
