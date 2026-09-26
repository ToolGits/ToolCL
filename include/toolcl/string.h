#ifndef TOOLCL_STRING_H
#define TOOLCL_STRING_H

#include <stddef.h>

size_t toolcl_string_length(const char *str);
int toolcl_string_equals(const char *a, const char *b);
int toolcl_string_compare(const char *a, const char *b);
int toolcl_string_contains(const char *str, const char *needle);
int toolcl_string_starts_with(const char *str, const char *prefix);
int toolcl_string_ends_with(const char *str, const char *suffix);

size_t toolcl_string_copy(
    char *destination,
    size_t destination_size,
    const char *source
);

#endif
