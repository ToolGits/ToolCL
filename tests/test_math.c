#include <assert.h>
#include <math.h>
#include <toolcl/math.h>

static int near(float a, float b)
{
    return fabsf(a - b) < 0.0001f;
}

int main(void)
{
    assert(near(toolcl_addf(2, 3), 5));
    assert(near(toolcl_subf(5, 3), 2));
    assert(near(toolcl_mulf(2, 3), 6));
    assert(near(toolcl_divf(6, 3), 2));
    assert(near(toolcl_absf(-5), 5));
    assert(near(toolcl_minf(2, 5), 2));
    assert(near(toolcl_maxf(2, 5), 5));
    assert(near(toolcl_clampf(10, 0, 5), 5));
    assert(near(toolcl_clampf(-1, 0, 5), 0));
    assert(near(toolcl_lerpf(0, 10, 0.5f), 5));
    assert(near(toolcl_radians(180), TOOLCL_PI));
    assert(near(toolcl_degrees(TOOLCL_PI), 180));

    return 0;
}
