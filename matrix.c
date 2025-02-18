#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include <ctype.h>

Matrix MatrixInput()
{
    Matrix tempMatrix;
    int value;
    char *buffer = NULL;
    size_t buffer_size = 0;
    char *chk;
    int positive_checker = 0;

    printf("Matrix Size\n");
    printf("-----------\n");
    printf("Remember, the matrix dimensions must be greater than zero.\n");

    do
    {
        printf("Enter matrix length: ");
        ssize_t n_chars_read = getline(&buffer, &buffer_size, stdin);

        value = (int)strtol(buffer, &chk, 10);
        if (!isspace(*chk) && *chk != 0)
        {
            printf("Error: Invalid input. Try again\n");
        }
        else if (value <= 0)
        {
            printf("Error: Length must be positive. Try again\n");
            ++positive_checker;
        }
        --positive_checker;
    } while (!isspace(*chk) && *chk != 0 || !positive_checker);
    tempMatrix.length = value;

    do
    {
        printf("Enter matrix height: ");
        ssize_t n_chars_read = getline(&buffer, &buffer_size, stdin);

        value = (int)strtol(buffer, &chk, 10);
        if (!isspace(*chk) && *chk != 0)
        {
            printf("Error: Invalid input. Try again\n");
        }
        else if (value <= 0)
        {
            printf("Error: Length must be positive. Try again\n");
            ++positive_checker;
        }
        --positive_checker;
    } while (!isspace(*chk) && *chk != 0 || !positive_checker);
    free(buffer);
    tempMatrix.height = value;

    tempMatrix.data = malloc(sizeof(Complex) * tempMatrix.height * tempMatrix.length);

    if (tempMatrix.data == NULL)
    {
        printf("Memory allocation failed. Exiting.\n");
        exit(1);
    }

    printf("Size of matrix: %d x %d\n", tempMatrix.height, tempMatrix.length);
    printf("Matrix Input\n");
    printf("---------------\n");
    printf("Input rules:\n");
    printf("- Enter real numbers (e.g., 5.2) or complex numbers (e.g., (3.5, 4))\n");

    int counter = 0;
    while (counter != (tempMatrix.length * tempMatrix.height))
    {
        Complex num;
        while (1)
        {
            if (scanf("%lg", &num.real) != 0)
            {
                num.imaginary = 0;
                break;
            }
            else if (scanf("(%lf,%lf)", &num.real, &num.imaginary) != 2)
            {
                printf("Error: Invalid format. Try again.\n");
                while (getchar() != '\n')
                    ;
                continue;
            }
            break;
        }
        tempMatrix.data[counter] = num;
        counter++;
    }

    return tempMatrix;
}

void MatrixOutput(Matrix matrix)
{
    if (matrix.data == NULL)
    {
        printf("Error: Invalid matrix\n");
        return;
    }

    for (int i = 0; i < matrix.height; i++)
    {
        for (int j = 0; j < matrix.length; j++)
        {
            Complex num = matrix.data[i * matrix.length + j];
            if (num.imaginary == 0)
            {
                printf("%g ", num.real);
            }
            else
            {
                printf("(%g%+gi) ", num.real, num.imaginary);
            }
        }
        printf("\n");
    }
}

void MatrixFree(Matrix *matrix)
{
    if (matrix->data != NULL)
    {
        free(matrix->data);
        matrix->data = NULL;
    }
    matrix->length = 0;
    matrix->height = 0;
}
