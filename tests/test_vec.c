#include <math.h>
#include <stdio.h>
#include <toolcl/vec2.h>
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

int main(void)
{
    ToolCL_Vec2 a2 = toolcl_vec2(3.0f, 4.0f);
    ToolCL_Vec2 b2 = toolcl_vec2(1.0f, 2.0f);
    ToolCL_Vec2 zero2 = toolcl_vec2(0.0f, 0.0f);

    ToolCL_Vec3 a3 = toolcl_vec3(1.0f, 2.0f, 3.0f);
    ToolCL_Vec3 b3 = toolcl_vec3(4.0f, 5.0f, 6.0f);
    ToolCL_Vec3 zero3 = toolcl_vec3(0.0f, 0.0f, 0.0f);

    CHECK_FLOAT(toolcl_vec2_length(a2), 5.0f);
    CHECK_FLOAT(toolcl_vec2_distance(a2, b2), sqrtf(8.0f));
    CHECK_FLOAT(toolcl_vec2_dot(a2, b2), 11.0f);

    CHECK_FLOAT(toolcl_vec2_add(a2, b2).x, 4.0f);
    CHECK_FLOAT(toolcl_vec2_add(a2, b2).y, 6.0f);

    CHECK_FLOAT(toolcl_vec2_sub(a2, b2).x, 2.0f);
    CHECK_FLOAT(toolcl_vec2_sub(a2, b2).y, 2.0f);

    CHECK_FLOAT(toolcl_vec2_mul(a2, 2.0f).x, 6.0f);
    CHECK_FLOAT(toolcl_vec2_mul(a2, 2.0f).y, 8.0f);

    CHECK_FLOAT(toolcl_vec2_normalize(a2).x, 0.6f);
    CHECK_FLOAT(toolcl_vec2_normalize(a2).y, 0.8f);

    CHECK(toolcl_vec2_normalize(zero2).x == 0.0f);
    CHECK(toolcl_vec2_normalize(zero2).y == 0.0f);

    CHECK_FLOAT(toolcl_vec3_length(toolcl_vec3(2.0f, 3.0f, 6.0f)), 7.0f);
    CHECK_FLOAT(toolcl_vec3_distance(a3, b3), sqrtf(27.0f));
    CHECK_FLOAT(toolcl_vec3_dot(a3, b3), 32.0f);

    CHECK_FLOAT(toolcl_vec3_add(a3, b3).x, 5.0f);
    CHECK_FLOAT(toolcl_vec3_add(a3, b3).y, 7.0f);
    CHECK_FLOAT(toolcl_vec3_add(a3, b3).z, 9.0f);

    CHECK_FLOAT(toolcl_vec3_sub(a3, b3).x, -3.0f);
    CHECK_FLOAT(toolcl_vec3_sub(a3, b3).y, -3.0f);
    CHECK_FLOAT(toolcl_vec3_sub(a3, b3).z, -3.0f);

    CHECK_FLOAT(toolcl_vec3_mul(a3, 2.0f).x, 2.0f);
    CHECK_FLOAT(toolcl_vec3_mul(a3, 2.0f).y, 4.0f);
    CHECK_FLOAT(toolcl_vec3_mul(a3, 2.0f).z, 6.0f);

    CHECK_FLOAT(toolcl_vec3_cross(a3, b3).x, -3.0f);
    CHECK_FLOAT(toolcl_vec3_cross(a3, b3).y, 6.0f);
    CHECK_FLOAT(toolcl_vec3_cross(a3, b3).z, -3.0f);

    CHECK_FLOAT(toolcl_vec3_normalize(toolcl_vec3(0.0f, 0.0f, 5.0f)).z, 1.0f);

    CHECK(toolcl_vec3_normalize(zero3).x == 0.0f);
    CHECK(toolcl_vec3_normalize(zero3).y == 0.0f);
    CHECK(toolcl_vec3_normalize(zero3).z == 0.0f);

    return 0;
}
