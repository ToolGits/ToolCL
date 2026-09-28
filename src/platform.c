#include <toolcl/platform.h>

ToolCL_Platform toolcl_get_platform(void)
{
#if defined(_WIN32)
    return TOOLCL_PLATFORM_WINDOWS;
#elif defined(__linux__)
    return TOOLCL_PLATFORM_LINUX;
#elif defined(__APPLE__) && defined(__MACH__)
    return TOOLCL_PLATFORM_MACOS;
#else
    return TOOLCL_PLATFORM_UNKNOWN;
#endif
}