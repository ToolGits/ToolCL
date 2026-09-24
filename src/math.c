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
    /* ToolCL defines division by zero as a deterministic zero result. */
    if (b == 0.0f)
        return 0.0f;

    return a / b;
}
