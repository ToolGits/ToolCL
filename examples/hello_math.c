#include <stdio.h>
#include <toolcl/math.h>

int main(void)
{
    printf("=== ToolCL Math Showcase ===\n\n");

    printf("2 + 2 = %.2f\n",
           toolcl_addf(2.0f, 2.0f));

    printf("4 + 4 = %.2f\n",
           toolcl_addf(4.0f, 4.0f));

    printf("4 - 3 = %.2f\n",
           toolcl_subf(4.0f, 3.0f));

    printf("13 - 7 = %.2f\n",
           toolcl_subf(13.0f, 7.0f));

    printf("120 + 1200 = %.2f\n",
           toolcl_addf(120.0f, 1200.0f));

    printf("15 * 4 = %.2f\n",
           toolcl_mulf(15.0f, 4.0f));

    printf("100 / 5 = %.2f\n",
           toolcl_divf(100.0f, 5.0f));

    printf("7 / 2 = %.2f\n",
           toolcl_divf(7.0f, 2.0f));

    return 0;
}