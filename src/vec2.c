#include <math.h>
#include <toolcl/vec2.h>

ToolCL_Vec2 toolcl_vec2(float x, float y)
{
    ToolCL_Vec2 v = {x, y};
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
    return sqrtf(v.x * v.x + v.y * v.y);
}
