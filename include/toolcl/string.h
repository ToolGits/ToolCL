#ifndef TOOLCL_STRING_H
#define TOOLCL_STRING_H

#include <stddef.h>

size_t toolcl_string_length(const char *str);

int toolcl_string_equals(const char *a,
                         const char *b);

#endif