#include <math.h>
#include <toolcl/vec2.h>

CLVec2 cl_vec2(float x, float y) {
    CLVec2 v = {x, y};
    return v;
}

CLVec2 cl_vec2_add(CLVec2 a, CLVec2 b) {
    return cl_vec2(a.x + b.x, a.y + b.y);
}

CLVec2 cl_vec2_sub(CLVec2 a, CLVec2 b) {
    return cl_vec2(a.x - b.x, a.y - b.y);
}

CLVec2 cl_vec2_mul(CLVec2 v, float scalar) {
    return cl_vec2(v.x * scalar, v.y * scalar);
}

float cl_vec2_length(CLVec2 v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}