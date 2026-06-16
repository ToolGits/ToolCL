#include <stdio.h>
#include <toolcl/string.h>

int main(void)
{
    printf("Length: %zu\n",
           toolcl_string_length("ToolCL"));

    if (toolcl_string_equals("ToolCL",
                             "ToolCL"))
    {
        printf("Strings are equal\n");
    }

    if (!toolcl_string_equals("ToolCL",
                              "Toollibs"))
    {
        printf("Strings are different\n");
    }

    return 0;
}