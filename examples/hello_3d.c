#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#include <toolcl/mat4.h>

static const char *vertex_shader_source =
    "#version 330 core\n"
    "layout (location = 0) in vec3 a_position;\n"
    "layout (location = 1) in vec3 a_color;\n"
    "uniform mat4 u_mvp;\n"
    "out vec3 v_color;\n"
    "void main() {\n"
    "    gl_Position = u_mvp * vec4(a_position, 1.0);\n"
    "    v_color = a_color;\n"
    "}\n";

static const char *fragment_shader_source =
    "#version 330 core\n"
    "in vec3 v_color;\n"
    "out vec4 frag_color;\n"
    "void main() {\n"
    "    frag_color = vec4(v_color, 1.0);\n"
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
        glfwCreateWindow(800, 600, "ToolCL - Hello 3D", NULL, NULL);

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
        /* Front */
        -0.5f,-0.5f, 0.5f, 1,0,0,
         0.5f,-0.5f, 0.5f, 0,1,0,
         0.5f, 0.5f, 0.5f, 0,0,1,

         0.5f, 0.5f, 0.5f, 0,0,1,
        -0.5f, 0.5f, 0.5f, 1,1,0,
        -0.5f,-0.5f, 0.5f, 1,0,0,

        /* Back */
         0.5f,-0.5f,-0.5f, 0,1,1,
        -0.5f,-0.5f,-0.5f, 1,0,1,
        -0.5f, 0.5f,-0.5f, 1,1,1,

        -0.5f, 0.5f,-0.5f, 1,1,1,
         0.5f, 0.5f,-0.5f, .5,.5,.5,
         0.5f,-0.5f,-0.5f, 0,1,1,

        /* Left */
        -0.5f,-0.5f,-0.5f, 1,0,1,
        -0.5f,-0.5f, 0.5f, 1,0,0,
        -0.5f, 0.5f, 0.5f, 0,1,0,

        -0.5f, 0.5f, 0.5f, 0,1,0,
        -0.5f, 0.5f,-0.5f, 1,1,1,
        -0.5f,-0.5f,-0.5f, 1,0,1,

        /* Right */
         0.5f,-0.5f, 0.5f, 0,1,0,
         0.5f,-0.5f,-0.5f, 0,1,1,
         0.5f, 0.5f,-0.5f, .5,.5,.5,

         0.5f, 0.5f,-0.5f, .5,.5,.5,
         0.5f, 0.5f, 0.5f, 0,0,1,
         0.5f,-0.5f, 0.5f, 0,1,0,

        /* Top */
        -0.5f, 0.5f, 0.5f, 0,1,0,
         0.5f, 0.5f, 0.5f, 0,0,1,
         0.5f, 0.5f,-0.5f, .5,.5,.5,

         0.5f, 0.5f,-0.5f, .5,.5,.5,
        -0.5f, 0.5f,-0.5f, 1,1,1,
        -0.5f, 0.5f, 0.5f, 0,1,0,

        /* Bottom */
        -0.5f,-0.5f,-0.5f, 1,0,1,
         0.5f,-0.5f,-0.5f, 0,1,1,
         0.5f,-0.5f, 0.5f, 0,1,0,

         0.5f,-0.5f, 0.5f, 0,1,0,
        -0.5f,-0.5f, 0.5f, 1,0,0,
        -0.5f,-0.5f,-0.5f, 1,0,1
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
        6 * sizeof(float),
        (void *)0
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        6 * sizeof(float),
        (void *)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

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

        ToolCL_Mat4 model =
            toolcl_mat4_mul(
                toolcl_mat4_rotate_y(time),
                toolcl_mat4_rotate_x(time * 0.7f)
            );

        model =
            toolcl_mat4_mul(
                model,
                toolcl_mat4_rotate_z(time * 0.35f)
            );

        ToolCL_Mat4 view =
            toolcl_mat4_translate(
                0.0f, 0.0f, -2.5f
            );

        ToolCL_Mat4 projection =
            toolcl_mat4_perspective(
                1.0471975512f,
                aspect,
                0.1f,
                100.0f
            );

        ToolCL_Mat4 view_model =
            toolcl_mat4_mul(view, model);

        ToolCL_Mat4 mvp =
            toolcl_mat4_mul(
                projection,
                view_model
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
            mvp.m
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
