#include <stdio.h>
#include <toolcl/logger.h>

void toolcl_log(const char *message)
{
    printf("[ToolCL] %s\n", message);
}

void toolcl_log_debug(const char *message)
{
    printf("[DEBUG] %s\n", message);
}

void toolcl_log_info(const char *message)
{
    printf("[INFO ] %s\n", message);
}

void toolcl_log_warn(const char *message)
{
    printf("[WARN ] %s\n", message);
}

void toolcl_log_error(const char *message)
{
    printf("[ERROR] %s\n", message);
}