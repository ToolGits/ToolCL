#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int lucky_number;
    int random_number;

    int round = 1;
    int lives = 3;

    printf("=== ToolCL Hello Random ===\n\n");

    printf("Choose your lucky number (0-9): ");
    scanf("%d", &lucky_number);

    if (lucky_number < 0 || lucky_number > 9)
    {
        printf("\nInvalid number.\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    while (lives > 0)
    {
        random_number = rand() % 10;

        printf("\n----------------------\n");
        printf("Round %d\n", round);
        printf("Lives: %d\n", lives);

        printf("Rolling...\n");
        printf("Result: %d\n", random_number);

        if (random_number == lucky_number)
        {
            printf("✔ Correct! Next round!\n");
            round++;
        }
        else
        {
            lives--;
            printf("✖ Wrong!\n");

            if (lives > 0)
                printf("Lives left: %d\n", lives);
        }
    }

    printf("\n======================\n");
    printf("Game Over!\n");
    printf("Final Round: %d\n", round);
    printf("======================\n");

    return 0;
}