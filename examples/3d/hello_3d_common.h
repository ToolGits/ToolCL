#ifndef TOOLCL_HELLO_3D_COMMON_H
#define TOOLCL_HELLO_3D_COMMON_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint toolcl_3d_compile_shader(
    GLenum type,
    const char *source
);

GLuint toolcl_3d_create_program(
    const char *vertex_source,
    const char *fragment_source
);

int toolcl_3d_create_window(
    GLFWwindow **window,
    int width,
    int height,
    const char *title
);

void toolcl_3d_begin_frame(void);
void toolcl_3d_end_frame(GLFWwindow *window);

#endif
