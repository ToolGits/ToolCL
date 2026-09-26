#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int choose_number(void)
{
    int number;

    while (1)
    {
        printf("Choose your lucky number (0-9): ");
        scanf("%d", &number);

        if (number >= 0 && number <= 9)
            return number;

        printf("Invalid number!\n\n");
    }
}

static int generate_random(int *last_random)
{
    if (*last_random != -1 && (rand() % 100) < 30)
        return *last_random;

    *last_random = rand() % 10;
    return *last_random;
}

static int ask_change_number(void)
{
    char answer;

    printf("Change lucky number? (y/n): ");
    scanf(" %c", &answer);

    return (answer == 'y' || answer == 'Y');
}

static int ask_play_again(void)
{
    char answer;

    printf("\nPlay again? (y/n): ");
    scanf(" %c", &answer);

    return (answer == 'y' || answer == 'Y');
}

static void play_random_game(void)
{
    int lives = 5;
    int round = 1;

    int lucky_number;
    int random_number;
    int last_random = -1;

    lucky_number = choose_number();

    while (lives > 0)
    {
        random_number = generate_random(&last_random);

        printf("\n====================\n");
        printf("Round : %d\n", round);
        printf("Lives : %d\n", lives);
        printf("====================\n");

        printf("Lucky Number : %d\n", lucky_number);
        printf("Rolling...\n");
        printf("Result : %d\n\n", random_number);

        if (random_number == lucky_number)
        {
            printf("✔ Correct! Next round!\n");
            round++;
        }
        else
        {
            lives--;

            printf("✖ Wrong!\n");

            if (lives <= 0)
                break;

            printf("Lives left: %d\n\n", lives);

            if (ask_change_number())
            {
                lucky_number = choose_number();
            }
        }
    }

    printf("\n====================\n");
    printf("Game Over!\n");
    printf("Final Round : %d\n", round);
    printf("====================\n");
}

int main(void)
{
    srand((unsigned int)time(NULL));

    printf("=== ToolCL Hello Random ===\n\n");

    do
    {
        play_random_game();
    }
    while (ask_play_again());

    printf("\nThanks for playing!\n");

    return 0;
}
