#include <stdio.h>
#include <stdlib.h>
#include "complex.h"
#include "matrix.h"
#include <ctype.h>

Matrix MatrixInput()
{
    Matrix tempMatrix;
    int value;
    char *buffer = NULL;
    size_t buffer_size = 0;
    char *chk;

    printf("\nMatrix Size\n");
    printf("-----------\n");
    printf("Remember, the matrix dimensions must be greater than zero.\n");

    do
    {
        printf("Enter matrix height: ");
        ssize_t n_chars_read = getline(&buffer, &buffer_size, stdin);

        value = (int)strtol(buffer, &chk, 10);
        if (!isspace(*chk) && *chk != 0)
        {
            printf("Error: Invalid input. Try again.\n");
        }
        else if (value <= 0)
        {
            printf("Error: Length must be positive. Try again.\n");
        }
    } while (!isspace(*chk) && *chk != 0 || value <= 0);
    free(buffer);
    tempMatrix.height = value;

    do
    {
        printf("Enter matrix length: ");
        ssize_t n_chars_read = getline(&buffer, &buffer_size, stdin);

        value = (int)strtol(buffer, &chk, 10);
        if (!isspace(*chk) && *chk != 0)
        {
            printf("Error: Invalid input. Try again.\n");
        }
        else if (value <= 0)
        {
            printf("Error: Length must be positive. Try again.\n");
        }
    } while (!isspace(*chk) && *chk != 0 || value <= 0);
    tempMatrix.length = value;

    tempMatrix.data = malloc(sizeof(Complex) * tempMatrix.height * tempMatrix.length);

    if (tempMatrix.data == NULL)
    {
        printf("Memory allocation failed. Exiting.\n");
        exit(1);
    }

    printf("\nSize of matrix: %d x %d\n\n", tempMatrix.height, tempMatrix.length);
    printf("Matrix Input\n");
    printf("------------\n");
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
                clear_input_buffer();
                continue;
            }
            break;
        }
        tempMatrix.data[counter] = num;
        counter++;
    }

    clear_input_buffer();
    return tempMatrix;
}

void MatrixOutput(Matrix matrix)
{
    if (matrix.data == NULL)
    {
        printf("Error: Invalid matrix.\n");
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

Matrix MatrixSum(Matrix a, Matrix b)
{
    Matrix tempMatrix = {0, 0, NULL};
    tempMatrix.height = a.height;
    tempMatrix.length = a.length;
    tempMatrix.data = malloc(sizeof(Complex) * a.height * a.length);
    for (int i = 0; i < a.height; ++i)
    {
        for (int j = 0; j < b.length; ++j)
        {
            tempMatrix.data[i * a.length + j] = ComplexSum(a.data[i * a.length + j], b.data[i * a.length + j], 1);
        }
    }

    return tempMatrix;
}

void MatrixFree(Matrix *mat)
{
    if (mat && mat->data)
    {
        free(mat->data);
        mat->data = NULL; // Prevent double free
        mat->height = 0;
        mat->length = 0;
    }
}

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
