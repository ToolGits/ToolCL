#include <toolcl/math.h>

int toolcl_add(int a, int b)
{
    return a + b;
}

int toolcl_sub(int a, int b)
{
    return a - b;
}

int toolcl_mul(int a, int b)
{
    return a * b;
}

int toolcl_div(int a, int b)
{
    if (b == 0)
        return 0;

    return a / b;
}