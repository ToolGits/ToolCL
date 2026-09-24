#include <math.h>
#include <toolcl/vec3.h>

ToolCL_Vec3 toolcl_vec3(float x, float y, float z)
{
    ToolCL_Vec3 v = {x, y, z};
    return v;
}

ToolCL_Vec3 toolcl_vec3_add(ToolCL_Vec3 a, ToolCL_Vec3 b)
{
    return toolcl_vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

ToolCL_Vec3 toolcl_vec3_sub(ToolCL_Vec3 a, ToolCL_Vec3 b)
{
    return toolcl_vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

ToolCL_Vec3 toolcl_vec3_mul(ToolCL_Vec3 v, float scalar)
{
    return toolcl_vec3(
        v.x * scalar,
        v.y * scalar,
        v.z * scalar
    );
}

float toolcl_vec3_length(ToolCL_Vec3 v)
{
    return sqrtf(
        v.x * v.x +
        v.y * v.y +
        v.z * v.z
    );
}

ToolCL_Vec3 toolcl_vec3_normalize(ToolCL_Vec3 v)
{
    float length = toolcl_vec3_length(v);

    if (length == 0.0f)
        return toolcl_vec3(0.0f, 0.0f, 0.0f);

    return toolcl_vec3_mul(v, 1.0f / length);
}

float toolcl_vec3_dot(ToolCL_Vec3 a, ToolCL_Vec3 b)
{
    return
        a.x * b.x +
        a.y * b.y +
        a.z * b.z;
}

ToolCL_Vec3 toolcl_vec3_cross(ToolCL_Vec3 a, ToolCL_Vec3 b)
{
    return toolcl_vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}
