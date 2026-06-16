#include <toolcl/string.h>

size_t toolcl_string_length(const char *str)
{
    size_t len = 0;

    while (str[len] != '\0')
    {
        len++;
    }

    return len;
}

int toolcl_string_equals(const char *a,
                         const char *b)
{
    size_t i = 0;

    while (a[i] != '\0' &&
           b[i] != '\0')
    {
        if (a[i] != b[i])
        {
            return 0;
        }

        i++;
    }

    return a[i] == b[i];
}