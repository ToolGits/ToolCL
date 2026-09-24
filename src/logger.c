#include <stdio.h>
#include <toolcl/logger.h>

static const char *toolcl_log_level_name(ToolCL_LogLevel level)
{
    switch (level)
    {
        case TOOLCL_DEBUG:
            return "DEBUG";

        case TOOLCL_INFO:
            return "INFO ";

        case TOOLCL_WARN:
            return "WARN ";

        case TOOLCL_ERROR:
            return "ERROR";

        default:
            return "UNKNOWN";
    }
}

void toolcl_log(const char *message)
{
    printf("[ToolCL] %s\n", message ? message : "(null)");
}

void toolcl_log_level(ToolCL_LogLevel level, const char *message)
{
    printf("[%s] %s\n",
           toolcl_log_level_name(level),
           message ? message : "(null)");
}

void toolcl_log_debug(const char *message)
{
    toolcl_log_level(TOOLCL_DEBUG, message);
}

void toolcl_log_info(const char *message)
{
    toolcl_log_level(TOOLCL_INFO, message);
}

void toolcl_log_warn(const char *message)
{
    toolcl_log_level(TOOLCL_WARN, message);
}

void toolcl_log_error(const char *message)
{
    toolcl_log_level(TOOLCL_ERROR, message);
}
