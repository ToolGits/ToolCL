#include <assert.h>
#include <toolcl/string.h>

int main(void)
{
    char buffer[8];

    assert(toolcl_string_length("ToolCL") == 6);
    assert(toolcl_string_equals("abc", "abc"));
    assert(!toolcl_string_equals("abc", "abd"));
    assert(toolcl_string_compare("abc", "abd") < 0);
    assert(toolcl_string_contains("ToolCL", "CL"));
    assert(toolcl_string_starts_with("ToolCL", "Tool"));
    assert(toolcl_string_ends_with("ToolCL", "CL"));
    assert(toolcl_string_copy(buffer, sizeof(buffer), "ToolCL") == 6);
    assert(toolcl_string_equals(buffer, "ToolCL"));

    return 0;
}
