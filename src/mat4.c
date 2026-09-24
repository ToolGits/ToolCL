#include <math.h>
#include <toolcl/mat4.h>

ToolCL_Mat4 toolcl_mat4_identity(void)
{
    ToolCL_Mat4 result = {{
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    }};

    return result;
}

ToolCL_Mat4 toolcl_mat4_mul(
    ToolCL_Mat4 a,
    ToolCL_Mat4 b
)
{
    ToolCL_Mat4 result = {{0}};

    for (int column = 0; column < 4; ++column) {
        for (int row = 0; row < 4; ++row) {
            result.m[column * 4 + row] =
                a.m[0 * 4 + row] * b.m[column * 4 + 0] +
                a.m[1 * 4 + row] * b.m[column * 4 + 1] +
                a.m[2 * 4 + row] * b.m[column * 4 + 2] +
                a.m[3 * 4 + row] * b.m[column * 4 + 3];
        }
    }

    return result;
}

ToolCL_Mat4 toolcl_mat4_translate(
    float x,
    float y,
    float z
)
{
    ToolCL_Mat4 result = toolcl_mat4_identity();

    result.m[12] = x;
    result.m[13] = y;
    result.m[14] = z;

    return result;
}

ToolCL_Mat4 toolcl_mat4_scale(
    float x,
    float y,
    float z
)
{
    ToolCL_Mat4 result = toolcl_mat4_identity();

    result.m[0] = x;
    result.m[5] = y;
    result.m[10] = z;

    return result;
}

ToolCL_Mat4 toolcl_mat4_rotate_x(float radians)
{
    float c = cosf(radians);
    float s = sinf(radians);

    ToolCL_Mat4 result = toolcl_mat4_identity();

    result.m[5] = c;
    result.m[6] = s;
    result.m[9] = -s;
    result.m[10] = c;

    return result;
}

ToolCL_Mat4 toolcl_mat4_rotate_y(float radians)
{
    float c = cosf(radians);
    float s = sinf(radians);

    ToolCL_Mat4 result = toolcl_mat4_identity();

    result.m[0] = c;
    result.m[2] = -s;
    result.m[8] = s;
    result.m[10] = c;

    return result;
}

ToolCL_Mat4 toolcl_mat4_rotate_z(float radians)
{
    float c = cosf(radians);
    float s = sinf(radians);

    ToolCL_Mat4 result = toolcl_mat4_identity();

    result.m[0] = c;
    result.m[1] = s;
    result.m[4] = -s;
    result.m[5] = c;

    return result;
}

ToolCL_Mat4 toolcl_mat4_perspective(
    float fov_radians,
    float aspect,
    float near_plane,
    float far_plane
)
{
    ToolCL_Mat4 result = {{0}};
    float tan_half_fov = tanf(fov_radians * 0.5f);

    result.m[0] = 1.0f / (aspect * tan_half_fov);
    result.m[5] = 1.0f / tan_half_fov;

    result.m[10] =
        -(far_plane + near_plane) /
        (far_plane - near_plane);

    result.m[11] = -1.0f;

    result.m[14] =
        -(2.0f * far_plane * near_plane) /
        (far_plane - near_plane);

    return result;
}

ToolCL_Vec3 toolcl_mat4_transform_vec3(
    ToolCL_Mat4 matrix,
    ToolCL_Vec3 vector
)
{
    float x =
        matrix.m[0] * vector.x +
        matrix.m[4] * vector.y +
        matrix.m[8] * vector.z +
        matrix.m[12];

    float y =
        matrix.m[1] * vector.x +
        matrix.m[5] * vector.y +
        matrix.m[9] * vector.z +
        matrix.m[13];

    float z =
        matrix.m[2] * vector.x +
        matrix.m[6] * vector.y +
        matrix.m[10] * vector.z +
        matrix.m[14];

    float w =
        matrix.m[3] * vector.x +
        matrix.m[7] * vector.y +
        matrix.m[11] * vector.z +
        matrix.m[15];

    if (w != 0.0f && w != 1.0f) {
        x /= w;
        y /= w;
        z /= w;
    }

    return toolcl_vec3(x, y, z);
}
