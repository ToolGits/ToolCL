#include <toolcl/logger.h>

int main(void)
{
    toolcl_log("Classic ToolCL log");

    toolcl_log_debug("Debug message");
    toolcl_log_info("Info message");
    toolcl_log_warn("Warning message");
    toolcl_log_error("Error message");

    return 0;
}