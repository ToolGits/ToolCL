#ifndef TOOLCL_VEC3_H
#define TOOLCL_VEC3_H

typedef struct {
    float x;
    float y;
    float z;
} ToolCL_Vec3;

ToolCL_Vec3 toolcl_vec3(float x, float y, float z);

ToolCL_Vec3 toolcl_vec3_add(ToolCL_Vec3 a, ToolCL_Vec3 b);
ToolCL_Vec3 toolcl_vec3_sub(ToolCL_Vec3 a, ToolCL_Vec3 b);
ToolCL_Vec3 toolcl_vec3_mul(ToolCL_Vec3 v, float scalar);

float toolcl_vec3_length(ToolCL_Vec3 v);
ToolCL_Vec3 toolcl_vec3_normalize(ToolCL_Vec3 v);

float toolcl_vec3_dot(ToolCL_Vec3 a, ToolCL_Vec3 b);
ToolCL_Vec3 toolcl_vec3_cross(ToolCL_Vec3 a, ToolCL_Vec3 b);

#endif
