#include <math.h>
#include <stdio.h>
#include <toolcl/mat4.h>
#include <toolcl/math.h>
#include <toolcl/vec3.h>

#define CHECK(condition) \
    do \
    { \
        if (!(condition)) \
        { \
            fprintf(stderr, "FAIL: %s\n", #condition); \
            return 1; \
        } \
    } while (0)

#define CHECK_FLOAT(a, b) \
    CHECK(fabsf((a) - (b)) < 0.0001f)

static int is_zero_matrix(ToolCL_Mat4 matrix)
{
    int i;

    for (i = 0; i < 16; i++)
    {
        if (matrix.data[i] != 0.0f)
            return 0;
    }

    return 1;
}

int main(void)
{
    ToolCL_Mat4 identity = toolcl_mat4_identity();
    ToolCL_Mat4 zero = toolcl_mat4_zero();
    ToolCL_Mat4 scale;
    ToolCL_Mat4 translation;
    ToolCL_Mat4 rotation;
    ToolCL_Mat4 perspective;
    ToolCL_Mat4 multiplication;
    ToolCL_Vec3 transformed;

    CHECK(identity.data[0] == 1.0f);
    CHECK(identity.data[5] == 1.0f);
    CHECK(identity.data[10] == 1.0f);
    CHECK(identity.data[15] == 1.0f);

    CHECK(is_zero_matrix(zero));

    scale = toolcl_mat4_scale(toolcl_vec3(2.0f, 3.0f, 4.0f));

    CHECK(scale.data[0] == 2.0f);
    CHECK(scale.data[5] == 3.0f);
    CHECK(scale.data[10] == 4.0f);
    CHECK(scale.data[15] == 1.0f);

    translation = toolcl_mat4_translate(toolcl_vec3(2.0f, 3.0f, 4.0f));

    CHECK(translation.data[12] == 2.0f);
    CHECK(translation.data[13] == 3.0f);
    CHECK(translation.data[14] == 4.0f);

    transformed = toolcl_mat4_transform_vec3(
        translation,
        toolcl_vec3(1.0f, 2.0f, 3.0f)
    );

    CHECK_FLOAT(transformed.x, 3.0f);
    CHECK_FLOAT(transformed.y, 5.0f);
    CHECK_FLOAT(transformed.z, 7.0f);

    transformed = toolcl_mat4_transform_vec3(
        scale,
        toolcl_vec3(1.0f, 2.0f, 3.0f)
    );

    CHECK_FLOAT(transformed.x, 2.0f);
    CHECK_FLOAT(transformed.y, 6.0f);
    CHECK_FLOAT(transformed.z, 12.0f);

    multiplication = toolcl_mat4_mul(identity, scale);

    CHECK_FLOAT(multiplication.data[0], scale.data[0]);
    CHECK_FLOAT(multiplication.data[5], scale.data[5]);
    CHECK_FLOAT(multiplication.data[10], scale.data[10]);
    CHECK_FLOAT(multiplication.data[15], scale.data[15]);

    rotation = toolcl_mat4_rotate_x(toolcl_radians(90.0f));
    transformed = toolcl_mat4_transform_vec3(
        rotation,
        toolcl_vec3(0.0f, 1.0f, 0.0f)
    );

    CHECK_FLOAT(transformed.x, 0.0f);
    CHECK_FLOAT(transformed.y, 0.0f);
    CHECK_FLOAT(transformed.z, 1.0f);

    rotation = toolcl_mat4_rotate_y(toolcl_radians(90.0f));
    transformed = toolcl_mat4_transform_vec3(
        rotation,
        toolcl_vec3(1.0f, 0.0f, 0.0f)
    );

    CHECK_FLOAT(transformed.x, 0.0f);
    CHECK_FLOAT(transformed.y, 0.0f);
    CHECK_FLOAT(transformed.z, -1.0f);

    rotation = toolcl_mat4_rotate_z(toolcl_radians(90.0f));
    transformed = toolcl_mat4_transform_vec3(
        rotation,
        toolcl_vec3(1.0f, 0.0f, 0.0f)
    );

    CHECK_FLOAT(transformed.x, 0.0f);
    CHECK_FLOAT(transformed.y, 1.0f);
    CHECK_FLOAT(transformed.z, 0.0f);

    perspective = toolcl_mat4_perspective(
        toolcl_radians(60.0f),
        16.0f / 9.0f,
        0.1f,
        100.0f
    );

    CHECK(!is_zero_matrix(perspective));
    CHECK_FLOAT(perspective.data[11], -1.0f);

    CHECK(is_zero_matrix(
        toolcl_mat4_perspective(
            0.0f,
            16.0f / 9.0f,
            0.1f,
            100.0f
        )
    ));

    CHECK(is_zero_matrix(
        toolcl_mat4_perspective(
            TOOLCL_PI,
            16.0f / 9.0f,
            0.1f,
            100.0f
        )
    ));

    CHECK(is_zero_matrix(
        toolcl_mat4_perspective(
            NAN,
            16.0f / 9.0f,
            0.1f,
            100.0f
        )
    ));

    CHECK(is_zero_matrix(
        toolcl_mat4_perspective(
            INFINITY,
            16.0f / 9.0f,
            0.1f,
            100.0f
        )
    ));

    CHECK(is_zero_matrix(
        toolcl_mat4_perspective(
            toolcl_radians(60.0f),
            0.0f,
            0.1f,
            100.0f
        )
    ));

    CHECK(is_zero_matrix(
        toolcl_mat4_perspective(
            toolcl_radians(60.0f),
            NAN,
            0.1f,
            100.0f
        )
    ));

    CHECK(is_zero_matrix(
        toolcl_mat4_perspective(
            toolcl_radians(60.0f),
            16.0f / 9.0f,
            0.0f,
            100.0f
        )
    ));

    CHECK(is_zero_matrix(
        toolcl_mat4_perspective(
            toolcl_radians(60.0f),
            16.0f / 9.0f,
            0.1f,
            0.1f
        )
    ));

    CHECK(is_zero_matrix(
        toolcl_mat4_perspective(
            toolcl_radians(60.0f),
            16.0f / 9.0f,
            10.0f,
            1.0f
        )
    ));

    {
        ToolCL_Mat4 invalid_w = toolcl_mat4_identity();

        invalid_w.data[15] = INFINITY;

        transformed = toolcl_mat4_transform_vec3(
            invalid_w,
            toolcl_vec3(4.0f, 5.0f, 6.0f)
        );

        CHECK_FLOAT(transformed.x, 4.0f);
        CHECK_FLOAT(transformed.y, 5.0f);
        CHECK_FLOAT(transformed.z, 6.0f);
    }

    return 0;
}
