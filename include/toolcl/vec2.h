#ifndef TOOLCL_VEC2_H
#define TOOLCL_VEC2_H

typedef struct {
    float x;
    float y;
} CLVec2;

CLVec2 cl_vec2(float x, float y);

CLVec2 cl_vec2_add(CLVec2 a, CLVec2 b);
CLVec2 cl_vec2_sub(CLVec2 a, CLVec2 b);
CLVec2 cl_vec2_mul(CLVec2 v, float scalar);

float cl_vec2_length(CLVec2 v);

#endif