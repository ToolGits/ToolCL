#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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

static int ask_replay(void)
{
    char answer;

    printf("\nPlay again? (y/n): ");
    scanf(" %c", &answer);

    return (answer == 'y' || answer == 'Y');
}

static int classic_mode(void)
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

    printf("\nLinux detected!\n");
    printf("All tests passed successfully!\n");

    printf("Game Over\n");
    return 0;
}

static int random_mode(void)
{
    const char *pool[] = {
        "A", "B", "C",
        "123", "1206",
        "Li", "nux",
        "Linux",
        "ToolCL",
        "D", "E", "F",
        "g",
        "win", "dows",
        "mac", "os",
        "Arch",
        "Steam", "Deck",
        "De", "bian",
        "git",
        "hub",
        "Six", "Seven"
    };

    int size = sizeof(pool) / sizeof(pool[0]);

    printf("=== RANDOM MODE ===\n\n");
    printf("Survive as long as you can...\n\n");

    int round = 1;

    while (1)
    {
        const char *expected = pool[rand() % size];

        printf("[Round %d] Write: %s\n", round, expected);

        if (!check_input(expected))
        {
            printf("Game Over at round %d\n", round);
            return 0;
        }

        round++;

        if (rand() % 10 == 0)
        {
            printf("\nContinue? (y/n): ");
            char c;
            scanf(" %c", &c);

            if (c != 'y' && c != 'Y')
                break;
        }
    }

    return 0;
}

int main(void)
{
    int mode;
    int running = 1;

    srand((unsigned int)time(NULL));

    while (running)
    {
        printf("=== ToolCL Hello World ===\n\n");

        printf("Select mode:\n");
        printf("[0] Classic Mode\n");
        printf("[1] Random Mode\n");
        printf("> ");

        scanf("%d", &mode);

        printf("\n");

        if (mode == 0)
            classic_mode();
        else
            random_mode();

        if (!ask_replay())
        {
            running = 0;
            printf("\nThanks for playing!\n");
        }
    }

    return 0;
}