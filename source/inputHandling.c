
#include <stdio.h>
#include <stdlib.h>
#include "../inc/inputHandling.h"

int getChoice(int a, int b)
{
    char *input = NULL;
    size_t inputSize = 0;
    int choice;
    int validInput = 0;

    do
    {
        printf("Choose an option (%d-%d):\n", a, b);
        printf("Enter your choice: ");

        if (getline(&input, &inputSize, stdin) == -1)
        {
            perror("Error: Invalid input");
            free(input);
            exit(1);
        }

        char *end_ptr;
        choice = (int)strtol(input, &end_ptr, 10);
        if (*end_ptr != '\n' && *end_ptr != '\0')
        {
            printf("Error: Please enter a valid number.\n");
        }
        else if (choice < a || choice > b)
        {
            printf("Error: Please enter a number between %d and %d.\n", a, b);
        }
        else
        {
            validInput = 1;
        }
    } while (!validInput);

    free(input);
    return choice;
}

unsigned int inputDimension()
{
    char *input = NULL;
    size_t inputSize = 0;
    unsigned int dim;
    int validInput = 0;

    do
    {
        if (getline(&input, &inputSize, stdin) == -1)
        {
            perror("Error: Invalid input");
            free(input);
            exit(1);
        }

        char *endPtr;
        dim = (unsigned int)strtol(input, &endPtr, 10);
        if (*endPtr != '\n' && *endPtr != '\0')
        {
            printf("Error: Please enter a valid number.\n");
        }
        else if (dim < 0)
        {
            printf("Error: matrix dimensions must be greater than zero\n");
        }
        else
        {
            validInput = 1;
        }
    } while (!validInput);

    free(input);
    return dim;
}

void invalidInput()
{
    printf("Error: Invalid format. Try again.\n");
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        ;
    }
}
