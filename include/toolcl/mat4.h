#ifndef TOOLCL_MAT4_H
#define TOOLCL_MAT4_H

#include <toolcl/vec3.h>

typedef struct {
    float m[16];
} ToolCL_Mat4;

ToolCL_Mat4 toolcl_mat4_identity(void);

ToolCL_Mat4 toolcl_mat4_mul(
    ToolCL_Mat4 a,
    ToolCL_Mat4 b
);

ToolCL_Mat4 toolcl_mat4_translate(
    float x,
    float y,
    float z
);

ToolCL_Mat4 toolcl_mat4_scale(
    float x,
    float y,
    float z
);

ToolCL_Mat4 toolcl_mat4_rotate_x(float radians);
ToolCL_Mat4 toolcl_mat4_rotate_y(float radians);
ToolCL_Mat4 toolcl_mat4_rotate_z(float radians);

ToolCL_Mat4 toolcl_mat4_perspective(
    float fov_radians,
    float aspect,
    float near_plane,
    float far_plane
);

ToolCL_Vec3 toolcl_mat4_transform_vec3(
    ToolCL_Mat4 matrix,
    ToolCL_Vec3 vector
);

#endif
