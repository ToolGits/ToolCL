#include <math.h>
#include <stdio.h>
#include <toolcl/math.h>

#define CHECK(condition) \
    do \
    { \
        if (!(condition)) \
        { \
            fprintf(stderr, "FAIL: %s\n", #condition); \
            return 1; \
        } \
    } while (0)

int main(void)
{
    CHECK(toolcl_addf(2.0f, 3.0f) == 5.0f);
    CHECK(toolcl_subf(5.0f, 3.0f) == 2.0f);
    CHECK(toolcl_mulf(2.0f, 3.0f) == 6.0f);
    CHECK(toolcl_divf(6.0f, 3.0f) == 2.0f);

    CHECK(toolcl_absf(-5.0f) == 5.0f);
    CHECK(toolcl_minf(2.0f, 3.0f) == 2.0f);
    CHECK(toolcl_maxf(2.0f, 3.0f) == 3.0f);

    CHECK(toolcl_clampf(5.0f, 0.0f, 10.0f) == 5.0f);
    CHECK(toolcl_clampf(-5.0f, 0.0f, 10.0f) == 0.0f);
    CHECK(toolcl_clampf(15.0f, 0.0f, 10.0f) == 10.0f);

    CHECK(toolcl_lerpf(0.0f, 10.0f, 0.5f) == 5.0f);

    CHECK(fabsf(toolcl_sinf(TOOLCL_PI * 0.5f) - 1.0f) < 0.0001f);
    CHECK(fabsf(toolcl_cosf(0.0f) - 1.0f) < 0.0001f);
    CHECK(fabsf(toolcl_tanf(0.0f)) < 0.0001f);
    CHECK(fabsf(toolcl_sqrtf(9.0f) - 3.0f) < 0.0001f);

    CHECK(fabsf(toolcl_radians(180.0f) - TOOLCL_PI) < 0.0001f);
    CHECK(fabsf(toolcl_degrees(TOOLCL_PI) - 180.0f) < 0.0001f);

    CHECK(toolcl_divf(1.0f, 0.0f) == 0.0f);
    CHECK(toolcl_sqrtf(-1.0f) == 0.0f);

    CHECK(toolcl_clampf(5.0f, 10.0f, 0.0f) == 5.0f);

    return 0;
}
