#include <assert.h>
#include <math.h>
#include <toolcl/vec2.h>
#include <toolcl/vec3.h>

static int near(float a, float b)
{
    return fabsf(a - b) < 0.0001f;
}

int main(void)
{
    ToolCL_Vec2 a = toolcl_vec2(3, 4);
    ToolCL_Vec2 n = toolcl_vec2_normalize(a);

    ToolCL_Vec3 x = toolcl_vec3(1, 0, 0);
    ToolCL_Vec3 y = toolcl_vec3(0, 1, 0);
    ToolCL_Vec3 z = toolcl_vec3_cross(x, y);

    assert(near(toolcl_vec2_length(a), 5));
    assert(near(n.x, 0.6f));
    assert(near(n.y, 0.8f));
    assert(near(toolcl_vec3_dot(x, y), 0));
    assert(near(z.x, 0));
    assert(near(z.y, 0));
    assert(near(z.z, 1));

    return 0;
}
