#ifndef TOOLCL_VEC2_H
#define TOOLCL_VEC2_H

typedef struct {
    float x;
    float y;
} ToolCL_Vec2;

ToolCL_Vec2 toolcl_vec2(float x, float y);

ToolCL_Vec2 toolcl_vec2_add(ToolCL_Vec2 a, ToolCL_Vec2 b);
ToolCL_Vec2 toolcl_vec2_sub(ToolCL_Vec2 a, ToolCL_Vec2 b);
ToolCL_Vec2 toolcl_vec2_mul(ToolCL_Vec2 v, float scalar);

float toolcl_vec2_length(ToolCL_Vec2 v);

#endif
