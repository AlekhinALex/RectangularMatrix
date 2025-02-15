#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix MatrixInput()
{
    Matrix tempMatrix;
    printf("Enter matrix length: ");
    scanf("%d", &tempMatrix.length);
    printf("Enter matrix height: ");
    scanf("%d", &tempMatrix.height);

    tempMatrix.data = malloc(sizeof(Complex) * tempMatrix.height * tempMatrix.length);
    if (tempMatrix.data == NULL)
    {
        printf("Error: Memory allocation failed\n");
        exit(1);
    }

    printf("Enter matrix:\n");
    int counter = 0;
    while (counter != (tempMatrix.length * tempMatrix.height))
    {
        Complex num;
        while (1)
        {
            if (scanf("%lg", &num.real) > 0)
            {
                num.imaginary = 0;
                break;
            }
            else if (scanf("(%lg,%lg)", &num.real, &num.imaginary) != 2)
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
