#include <stdio.h>
#include <toolcl/vec2.h>

int main(void)
{
    ToolCL_Vec2 a = toolcl_vec2(2.0f, 3.0f);
    ToolCL_Vec2 b = toolcl_vec2(4.0f, 1.0f);

    ToolCL_Vec2 c = toolcl_vec2_add(a, b);

    printf("Vec2 result: (%f, %f)\n", c.x, c.y);

    return 0;
}
