#include <math.h>
#include <toolcl/math.h>

float toolcl_addf(float a, float b)
{
    return a + b;
}

float toolcl_subf(float a, float b)
{
    return a - b;
}

float toolcl_mulf(float a, float b)
{
    return a * b;
}

float toolcl_divf(float a, float b)
{
    return b == 0.0f ? 0.0f : a / b;
}

float toolcl_absf(float value)
{
    return fabsf(value);
}

float toolcl_minf(float a, float b)
{
    return a < b ? a : b;
}

float toolcl_maxf(float a, float b)
{
    return a > b ? a : b;
}

float toolcl_clampf(float value, float min, float max)
{
    float temp;

    if (min > max)
    {
        temp = min;
        min = max;
        max = temp;
    }

    return toolcl_maxf(min, toolcl_minf(value, max));
}

float toolcl_lerpf(float a, float b, float t)
{
    return a + (b - a) * t;
}

float toolcl_sinf(float radians)
{
    return sinf(radians);
}

float toolcl_cosf(float radians)
{
    return cosf(radians);
}

float toolcl_tanf(float radians)
{
    return tanf(radians);
}

float toolcl_sqrtf(float value)
{
    return value < 0.0f ? 0.0f : sqrtf(value);
}

float toolcl_radians(float degrees)
{
    return degrees * (TOOLCL_PI / 180.0f);
}

float toolcl_degrees(float radians)
{
    return radians * (180.0f / TOOLCL_PI);
}
