#include <stdio.h>
#include "toolcl/logger.h"

void toolcl_log(const char *message)
{
    printf("[ToolCL] %s\n", message);
}