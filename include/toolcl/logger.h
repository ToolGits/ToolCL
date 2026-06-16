#ifndef TOOLCL_LOGGER_H
#define TOOLCL_LOGGER_H

typedef enum
{
    TOOLCL_DEBUG,
    TOOLCL_INFO,
    TOOLCL_WARN,
    TOOLCL_ERROR
} ToolCL_LogLevel;

void toolcl_log(const char *message);

void toolcl_log_debug(const char *message);
void toolcl_log_info(const char *message);
void toolcl_log_warn(const char *message);
void toolcl_log_error(const char *message);

#endif