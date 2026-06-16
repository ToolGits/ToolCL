#include <stdio.h>
#include "toolcl/math.h"

int main(void)
{
    int result = toolcl_add(2, 2);

    result = toolcl_add(result, 2);

    printf("Result: %d\n", result);

    return 0;
}