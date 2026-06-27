#include <stdio.h>
#include <string.h>
#include <toolcl/hello_world.h>

static int check_input(const char *expected)
{
    char input[64];

    printf("> ");
    scanf("%63s", input);

    if (strcmp(input, expected) == 0)
    {
        printf("✔ Correct!\n\n");
        return 1;
    }

    printf("✖ Wrong! Expected: %s\n\n", expected);
    return 0;
}

/* =========================
   HELLO WORLD TEST FLOW
========================= */

int toolcl_hello_world_run(void)
{
    printf("=== ToolCL Hello World Test ===\n\n");

    printf("Write: A\n");
    if (!check_input("A")) return 0;

    printf("Write: B\n");
    if (!check_input("B")) return 0;

    printf("Write: C\n");
    if (!check_input("C")) return 0;

    printf("Write: 123\n");
    if (!check_input("123")) return 0;

    printf("Write: 1206\n");
    if (!check_input("1206")) return 0;

    printf("Write: Li\n");
    if (!check_input("Li")) return 0;

    printf("Write: nux\n");
    if (!check_input("nux")) return 0;

    printf("\n✔ Linux detected!\n");
    printf("✔ All tests passed successfully!\n");

    return 1;
}