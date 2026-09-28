#ifndef TOOLCL_PLATFORM_H
#define TOOLCL_PLATFORM_H

typedef enum {
    TOOLCL_PLATFORM_LINUX,
    TOOLCL_PLATFORM_WINDOWS,
    TOOLCL_PLATFORM_MACOS,
    TOOLCL_PLATFORM_UNKNOWN
} ToolCL_Platform;

ToolCL_Platform toolcl_get_platform(void);

#endif