#include <toolcl/string.h>

size_t toolcl_string_length(const char *str)
{
    size_t length = 0;

    if (!str)
        return 0;

    while (str[length])
        length++;

    return length;
}

int toolcl_string_equals(const char *a, const char *b)
{
    size_t i = 0;

    if (!a || !b)
        return a == b;

    while (a[i] && b[i])
    {
        if (a[i] != b[i])
            return 0;

        i++;
    }

    return a[i] == b[i];
}

int toolcl_string_compare(const char *a, const char *b)
{
    size_t i = 0;

    if (!a || !b)
        return a == b ? 0 : (a ? 1 : -1);

    while (a[i] && b[i] && a[i] == b[i])
        i++;

    return (unsigned char)a[i] - (unsigned char)b[i];
}

int toolcl_string_contains(const char *str, const char *needle)
{
    size_t i;
    size_t j;

    if (!str || !needle)
        return 0;

    if (!needle[0])
        return 1;

    for (i = 0; str[i]; i++)
    {
        for (j = 0; needle[j] && str[i + j] == needle[j]; j++)
            ;

        if (!needle[j])
            return 1;
    }

    return 0;
}

int toolcl_string_starts_with(const char *str, const char *prefix)
{
    size_t i;

    if (!str || !prefix)
        return 0;

    for (i = 0; prefix[i]; i++)
    {
        if (str[i] != prefix[i])
            return 0;
    }

    return 1;
}

int toolcl_string_ends_with(const char *str, const char *suffix)
{
    size_t str_length;
    size_t suffix_length;
    size_t i;

    if (!str || !suffix)
        return 0;

    str_length = toolcl_string_length(str);
    suffix_length = toolcl_string_length(suffix);

    if (suffix_length > str_length)
        return 0;

    for (i = 0; i < suffix_length; i++)
    {
        if (str[str_length - suffix_length + i] != suffix[i])
            return 0;
    }

    return 1;
}

size_t toolcl_string_copy(
    char *destination,
    size_t destination_size,
    const char *source
)
{
    size_t length;
    size_t copy_length;
    size_t i;

    if (!destination || destination_size == 0)
        return source ? toolcl_string_length(source) : 0;

    if (!source)
    {
        destination[0] = '\0';
        return 0;
    }

    length = toolcl_string_length(source);
    copy_length = length < destination_size - 1
        ? length
        : destination_size - 1;

    for (i = 0; i < copy_length; i++)
        destination[i] = source[i];

    destination[copy_length] = '\0';

    return length;
}
