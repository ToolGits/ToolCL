#ifndef TOOLCL_MATH_H
#define TOOLCL_MATH_H

#define TOOLCL_PI 3.14159265358979323846f

float toolcl_addf(float a, float b);
float toolcl_subf(float a, float b);
float toolcl_mulf(float a, float b);
float toolcl_divf(float a, float b);

float toolcl_absf(float value);
float toolcl_minf(float a, float b);
float toolcl_maxf(float a, float b);
float toolcl_clampf(float value, float min, float max);
float toolcl_lerpf(float a, float b, float t);

float toolcl_sinf(float radians);
float toolcl_cosf(float radians);
float toolcl_tanf(float radians);
float toolcl_sqrtf(float value);

float toolcl_radians(float degrees);
float toolcl_degrees(float radians);

#endif
