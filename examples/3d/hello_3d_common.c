#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "hello_3d_common.h"

GLuint toolcl_3d_compile_shader(
    GLenum type,
    const char *source
)
{
    GLuint shader;
    GLint success;
    char log[1024];

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(
            shader,
            sizeof(log),
            NULL,
            log
        );

        fprintf(stderr, "%s\n", log);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint toolcl_3d_create_program(
    const char *vertex_source,
    const char *fragment_source
)
{
    GLuint vertex;
    GLuint fragment;
    GLuint program;
    GLint success;
    char log[1024];

    vertex = toolcl_3d_compile_shader(
        GL_VERTEX_SHADER,
        vertex_source
    );

    fragment = toolcl_3d_compile_shader(
        GL_FRAGMENT_SHADER,
        fragment_source
    );

    if (!vertex || !fragment)
        return 0;

    program = glCreateProgram();

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    glGetProgramiv(
        program,
        GL_LINK_STATUS,
        &success
    );

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    if (!success)
    {
        glGetProgramInfoLog(
            program,
            sizeof(log),
            NULL,
            log
        );

        fprintf(stderr, "%s\n", log);
        glDeleteProgram(program);
        return 0;
    }

    return program;
}

int toolcl_3d_create_window(
    GLFWwindow **window,
    int width,
    int height,
    const char *title
)
{
    if (!glfwInit())
        return 0;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    *window = glfwCreateWindow(
        width,
        height,
        title,
        NULL,
        NULL
    );

    if (!*window)
    {
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(*window);

    if (glewInit() != GLEW_OK)
    {
        glfwDestroyWindow(*window);
        glfwTerminate();
        return 0;
    }

    glViewport(0, 0, width, height);

    return 1;
}

void toolcl_3d_begin_frame(void)
{
    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );
}

void toolcl_3d_end_frame(GLFWwindow *window)
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}
