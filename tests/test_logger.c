#include <assert.h>
#include <toolcl/logger.h>

int main(void)
{
    toolcl_set_log_level(TOOLCL_DEBUG);
    assert(toolcl_get_log_level() == TOOLCL_DEBUG);

    toolcl_set_log_level(TOOLCL_WARN);
    assert(toolcl_get_log_level() == TOOLCL_WARN);

    toolcl_set_log_level(TOOLCL_ERROR);
    assert(toolcl_get_log_level() == TOOLCL_ERROR);

    toolcl_set_log_level(TOOLCL_INFO);
    assert(toolcl_get_log_level() == TOOLCL_INFO);

    return 0;
}
