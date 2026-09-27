#include <math.h>
#include <toolcl/mat4.h>
#include <toolcl/math.h>

ToolCL_Mat4 toolcl_mat4_zero(void)
{
    ToolCL_Mat4 result = { { 0.0f } };
    return result;
}

ToolCL_Mat4 toolcl_mat4_identity(void)
{
    ToolCL_Mat4 result = toolcl_mat4_zero();

    result.data[0] = 1.0f;
    result.data[5] = 1.0f;
    result.data[10] = 1.0f;
    result.data[15] = 1.0f;

    return result;
}

ToolCL_Mat4 toolcl_mat4_mul(ToolCL_Mat4 a, ToolCL_Mat4 b)
{
    ToolCL_Mat4 result = toolcl_mat4_zero();
    int row;
    int column;
    int index;

    for (column = 0; column < 4; column++)
    {
        for (row = 0; row < 4; row++)
        {
            index = column * 4 + row;

            result.data[index] =
                a.data[row] * b.data[column * 4] +
                a.data[4 + row] * b.data[column * 4 + 1] +
                a.data[8 + row] * b.data[column * 4 + 2] +
                a.data[12 + row] * b.data[column * 4 + 3];
        }
    }

    return result;
}

ToolCL_Mat4 toolcl_mat4_translate(ToolCL_Vec3 position)
{
    ToolCL_Mat4 result = toolcl_mat4_identity();

    result.data[12] = position.x;
    result.data[13] = position.y;
    result.data[14] = position.z;

    return result;
}

ToolCL_Mat4 toolcl_mat4_scale(ToolCL_Vec3 scale)
{
    ToolCL_Mat4 result = toolcl_mat4_identity();

    result.data[0] = scale.x;
    result.data[5] = scale.y;
    result.data[10] = scale.z;

    return result;
}

ToolCL_Mat4 toolcl_mat4_rotate_x(float radians)
{
    ToolCL_Mat4 result = toolcl_mat4_identity();
    float c = toolcl_cosf(radians);
    float s = toolcl_sinf(radians);

    result.data[5] = c;
    result.data[6] = s;
    result.data[9] = -s;
    result.data[10] = c;

    return result;
}

ToolCL_Mat4 toolcl_mat4_rotate_y(float radians)
{
    ToolCL_Mat4 result = toolcl_mat4_identity();
    float c = toolcl_cosf(radians);
    float s = toolcl_sinf(radians);

    result.data[0] = c;
    result.data[2] = -s;
    result.data[8] = s;
    result.data[10] = c;

    return result;
}

ToolCL_Mat4 toolcl_mat4_rotate_z(float radians)
{
    ToolCL_Mat4 result = toolcl_mat4_identity();
    float c = toolcl_cosf(radians);
    float s = toolcl_sinf(radians);

    result.data[0] = c;
    result.data[1] = s;
    result.data[4] = -s;
    result.data[5] = c;

    return result;
}

ToolCL_Mat4 toolcl_mat4_perspective(
    float fov_radians,
    float aspect,
    float near_plane,
    float far_plane
)
{
    ToolCL_Mat4 result = toolcl_mat4_zero();
    float tan_half_fov;
    float range;

    if (!isfinite(fov_radians) ||
        fov_radians <= 0.0f ||
        fov_radians >= TOOLCL_PI)
        return result;

    if (!isfinite(aspect) || aspect <= 0.0f)
        return result;

    if (!isfinite(near_plane) || near_plane <= 0.0f)
        return result;

    if (!isfinite(far_plane) || far_plane <= near_plane)
        return result;

    tan_half_fov = toolcl_tanf(fov_radians * 0.5f);

    if (!isfinite(tan_half_fov) || tan_half_fov <= 0.0f)
        return result;

    range = far_plane - near_plane;

    if (!isfinite(range) || range <= 0.0f)
        return result;

    result.data[0] = 1.0f / (aspect * tan_half_fov);
    result.data[5] = 1.0f / tan_half_fov;
    result.data[10] = -(far_plane + near_plane) / range;
    result.data[11] = -1.0f;
    result.data[14] = -(2.0f * far_plane * near_plane) / range;

    if (!isfinite(result.data[0]) ||
        !isfinite(result.data[5]) ||
        !isfinite(result.data[10]) ||
        !isfinite(result.data[14]))
        return toolcl_mat4_zero();

    return result;
}

ToolCL_Vec3 toolcl_mat4_transform_vec3(
    ToolCL_Mat4 matrix,
    ToolCL_Vec3 vector
)
{
    float x;
    float y;
    float z;
    float w;

    x =
        matrix.data[0] * vector.x +
        matrix.data[4] * vector.y +
        matrix.data[8] * vector.z +
        matrix.data[12];

    y =
        matrix.data[1] * vector.x +
        matrix.data[5] * vector.y +
        matrix.data[9] * vector.z +
        matrix.data[13];

    z =
        matrix.data[2] * vector.x +
        matrix.data[6] * vector.y +
        matrix.data[10] * vector.z +
        matrix.data[14];

    w =
        matrix.data[3] * vector.x +
        matrix.data[7] * vector.y +
        matrix.data[11] * vector.z +
        matrix.data[15];

    if (!isfinite(w))
        return vector;

    if (w != 0.0f && w != 1.0f)
    {
        x /= w;
        y /= w;
        z /= w;
    }

    return toolcl_vec3(x, y, z);
}
