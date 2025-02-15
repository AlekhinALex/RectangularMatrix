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
    tempMatrix.data = realloc(tempMatrix.data, sizeof(Complex) * tempMatrix.height * tempMatrix.length);
    printf("Enter matrix:\n");
    int counter = 0;
    while (counter != (tempMatrix.length * tempMatrix.height))
    {
        Complex num;
        if (scanf("%lg", &num.real) > 0)
        {
            num.imaginary = 0;
        }
        else if (scanf("(%lg,%lg)", &num.real, &num.imaginary) != 2)
        {
            printf("Error: Invalid format. Try again.\n");
            while (getchar() != '\n')
                ;
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

    int counter = 1;
    for (int i = 0; i < matrix.length * matrix.height; i++)
    {
        if (matrix.data[i].imaginary == 0)
        {
            printf("%g ", matrix.data[i].real);
        }
        else
        {
            printf("(%g+%gi) ", matrix.data[i].real, matrix.data[i].imaginary);
        }
        if (counter == matrix.length)
        {
            printf("\n");
            counter = 0;
        }
        counter++;
    }
}