#include <stdio.h>
#include <toolcl/vec2.h>

int main() {
    CLVec2 a = cl_vec2(2, 3);
    CLVec2 b = cl_vec2(4, 1);

    CLVec2 c = cl_vec2_add(a, b);

    printf("Vec2 result: (%f, %f)\n", c.x, c.y);

    return 0;
}