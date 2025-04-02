
#include <stdio.h>
#include <stdlib.h>

#include "../inc/inputHandling.h"
#include "../inc/errorHandling.h"

#include "../inc/integer.h"
#include "../inc/double.h"
#include "../inc/complex.h"
#include "../inc/matrix.h"

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

        // TODO check memory leak
        if (getline(&input, &inputSize, stdin) == -1)
        {
            printf("Error: Invalid input");
            free(input);
            return -1;
        }

        char *endPtr;
        choice = (int)strtol(input, &endPtr, 10);
        if (*endPtr != '\n' && *endPtr != '\0')
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

//* Constructors for matrices

void createNewMatrix(unsigned int height, unsigned int length, const typeInfo *type, Matrix *matrix)
{
    matrix->height = height;
    matrix->length = length;
    matrix->typeInfo = type;
    matrix->data = malloc(matrix->height * matrix->length * matrix->typeInfo->size());
}

// for addition and etc.
void setupMatrix(int height, int length, const typeInfo *type, Matrix *matrix)
{
    matrix->height = height;
    matrix->length = length;
    matrix->typeInfo = type;
}
