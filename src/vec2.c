#include <math.h>
#include <toolcl/vec2.h>

ToolCL_Vec2 toolcl_vec2(float x, float y)
{
    ToolCL_Vec2 v = { x, y };
    return v;
}

ToolCL_Vec2 toolcl_vec2_add(ToolCL_Vec2 a, ToolCL_Vec2 b)
{
    return toolcl_vec2(a.x + b.x, a.y + b.y);
}

ToolCL_Vec2 toolcl_vec2_sub(ToolCL_Vec2 a, ToolCL_Vec2 b)
{
    return toolcl_vec2(a.x - b.x, a.y - b.y);
}

ToolCL_Vec2 toolcl_vec2_mul(ToolCL_Vec2 v, float scalar)
{
    return toolcl_vec2(v.x * scalar, v.y * scalar);
}

float toolcl_vec2_length(ToolCL_Vec2 v)
{
    return hypotf(v.x, v.y);
}

float toolcl_vec2_dot(ToolCL_Vec2 a, ToolCL_Vec2 b)
{
    return a.x * b.x + a.y * b.y;
}

float toolcl_vec2_distance(ToolCL_Vec2 a, ToolCL_Vec2 b)
{
    return hypotf(a.x - b.x, a.y - b.y);
}

ToolCL_Vec2 toolcl_vec2_normalize(ToolCL_Vec2 v)
{
    float length = toolcl_vec2_length(v);

    if (length == 0.0f)
        return toolcl_vec2(0.0f, 0.0f);

    return toolcl_vec2(v.x / length, v.y / length);
}
