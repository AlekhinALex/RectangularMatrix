#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../inc/typeInfo.h"
#include "../inc/integer.h"
#include "../inc/double.h"
#include "../inc/complex.h"
#include "../inc/matrix.h"
#include "../inc/inputHandling.h"

void checkComponentsTypes(const Matrix *matrix1, const Matrix *matrix2)
{
    if (matrix1->typeComponents != matrix2->typeComponents)
    {
        printf("Error: Matrices must have identicals types. Try again.\n");
        return;
    }
}

void addMatrix(const Matrix *matrix1, const Matrix *matrix2, Matrix *result)
{

    if (matrix1->height != matrix2->height || matrix1->length != matrix2->length)
    {
        printf("Error: Matrices must have identicals sizes. Try again.\n");
        return;
    }
    checkComponentsTypes(matrix1, matrix2);

    result->height = matrix1->height;
    result->length = matrix1->length;
    result->typeComponents = matrix1->typeComponents;
    result->typeInfo = matrix1->typeInfo;

    allocateMatrixElements(result, matrix1);

    // matrix addition
    for (int i = 0; i < matrix1->height; i++)
    {
        for (int j = 0; j < matrix1->length; j++)
        {
            result->typeInfo->add(matrix1->data[i * matrix1->length + j],
                                  matrix2->data[i * matrix1->length + j],
                                  result->data[i * matrix1->length + j]);
        }
    }
}

void multiplyMatrix(const Matrix *matrix1, const Matrix *matrix2, Matrix *result)
{
    if (matrix1->length != matrix2->height)
    {
        printf("Error: Incompatible matrix dimensions for multiplication: %ux%u and %ux%u\n",
               matrix1->height, matrix1->length, matrix2->height, matrix2->length);
        return;
    }

    checkComponentsTypes(matrix1, matrix2);

    result->height = matrix1->height;
    result->length = matrix2->length;
    result->typeComponents = matrix1->typeComponents;

    result->typeInfo = matrix1->typeInfo;
    void *temp = NULL;
    allocateMatrixElements(result, matrix1);

    if (result->typeComponents == COMPLEX)
    {
        Complex *tempComplex = malloc(sizeof(Complex));
        Complex *srcComplex = (Complex *)result->data[0];

        tempComplex->type = srcComplex->type;
        tempComplex = result->typeInfo->allocate(tempComplex->type);

        temp = tempComplex;
    }
    else
    {
        temp = malloc(result->typeInfo->size);
    }

    // matrix multiplication
    for (int i = 0; i < matrix1->height; i++)
    {
        for (int j = 0; j < matrix2->length; j++)
        {
            for (int k = 0; k < matrix1->length; k++)
            {

                const void *elemA = matrix1->data[i * matrix1->length + k];
                const void *elemB = matrix2->data[k * matrix2->length + j];
                void *elemResult = result->data[i * result->length + j];
                // a[i][k] * b[k][j]
                result->typeInfo->multiply(elemA, elemB, temp);
                result->typeInfo->add(elemResult, temp, elemResult);
            }
        }
    }

    result->typeInfo->Free(temp);
}

void allocateMatrixElements(Matrix *matrixDest, const Matrix *matrixSrc)
{
    if (!matrixDest || !matrixSrc)
    {
        printf("Error: NULL matrix pointer\n");
        return;
    }

    matrixDest->data = malloc(matrixDest->height * matrixDest->length * sizeof(void *));

    for (int i = 0; i < matrixDest->height * matrixDest->length; i++)
    {

        if (matrixDest->typeComponents == COMPLEX)
        {
            Complex *srcElement = (Complex *)matrixSrc->data[0];
            Complex *newComplex = malloc(sizeof(Complex));

            newComplex->type = srcElement->type;
            newComplex = matrixDest->typeInfo->allocate(newComplex->type);

            matrixDest->data[i] = newComplex;
        }
        else
        {
            matrixDest->data[i] = matrixDest->typeInfo->allocate(matrixDest->typeComponents);
        }
    }
}

void inputMatrix(Matrix *matrix)
{

    matrix->data = NULL;
    matrix->height = 0;
    matrix->length = 0;
    matrix->typeInfo = NULL;

    int typeHolder = 0;
    printf("Enter what types of data will be stored in the matrix:\n");
    printf("1) Real numbers\n");
    printf("2) Integers\n");
    printf("3) Complex numbers\n");
    typeHolder = getChoice(1, 3);

    switch (typeHolder)
    {
    case 1:
        matrix->typeComponents = DOUBLE;
        matrix->typeInfo = getTypeInfoDouble();
        break;
    case 2:
        matrix->typeComponents = INT;
        matrix->typeInfo = getTypeInfoInt();
        break;
    case 3:
        matrix->typeComponents = COMPLEX;
        matrix->typeInfo = getTypeInfoComplex();
        break;
    default:
        break;
    }

    printf("\nMatrix Size\n");
    printf("-----------\n");
    printf("Remember, the matrix dimensions must be greater than zero.\n");

    printf("Enter matrix height: ");
    matrix->height = inputDimension();

    printf("Enter matrix length: ");
    matrix->length = inputDimension();

    printf("\nSize of matrix: %ux%u\n\n", matrix->height, matrix->length);
    printf("Matrix Input\n");
    printf("------------\n");

    int complexChoice = 0;
    switch (typeHolder)
    {
    case 1:
        printf("Input rules:\n");
        printf("Enter real numbers (e.g., 5.2)\n");
        break;
    case 2:
        printf("Input rules:\n");
        printf("Enter integer numbers (e.g., 5)\n");
        break;
    case 3:
    {
        printf("What types of data will be stored in the complex number?\n");
        printf("1) Real numbers\n");
        printf("2) Integers\n");
        complexChoice = getChoice(1, 2);
        printf("Input rules:\n");
        if (complexChoice == 1)
        {
            printf("Enter complex numbers (e.g., (3.5, 4.7))\n");
        }
        else if (complexChoice == 2)
        {
            printf("Enter complex numbers (e.g., (3, 4))\n");
        }
    }
    break;
    default:
        break;
    }

    setupMatrixElements(matrix, complexChoice);

    for (int i = 0; i < matrix->height; i++)
    {
        for (int j = 0; j < matrix->length; j++)
        {

            int validInput = 0;
            while (!validInput)
            {
                switch (typeHolder)
                {
                case 1:
                { //* double
                    double value;
                    if (scanf("%lf", &value) == 1)
                    {
                        *(double *)matrix->data[i * matrix->length + j] = value;
                        validInput = 1;
                    }
                    else
                    {
                        invalidInput();
                        clearInputBuffer();
                    }
                }
                break;
                case 2:
                { //* Integers
                    int value;
                    if (scanf("%d", &value) == 1)
                    {
                        *(int *)matrix->data[i * matrix->length + j] = value;
                        validInput = 1;
                    }
                    else
                    {
                        invalidInput();
                        clearInputBuffer();
                    }
                }
                break;
                case 3:
                { //* Complex numbers
                    Complex *value;

                    if (complexChoice == 1)
                    {
                        value = matrix->typeInfo->allocate(DOUBLE);
                        double tempImaginary;
                        double tempReal;

                        value->type = DOUBLE;
                        value->real = malloc(sizeof(double));
                        value->imaginary = malloc(sizeof(double));

                        //! NOT WORKING or does it?
                        if (scanf(" (%lf, %lf)", &tempReal, &tempImaginary) != 2)
                        {
                            printf("WHAT I SEE: %lf and %lf\n", tempReal, tempImaginary);
                            invalidInput();
                            clearInputBuffer();
                        }
                        else
                        {
                            *(double *)value->real = tempReal;
                            *(double *)value->imaginary = tempImaginary;

                            matrix->data[i * matrix->length + j] = value;
                            validInput = 1;
                        }
                    }
                    else if (complexChoice == 2)
                    {
                        value = matrix->typeInfo->allocate(INT);
                        int tempImaginary;
                        int tempReal;

                        value->type = INT;
                        value->real = malloc(sizeof(int));
                        value->imaginary = malloc(sizeof(int));

                        if (scanf(" (%d ,%d)", &tempReal, &tempImaginary) != 2)
                        {
                            invalidInput();
                            clearInputBuffer();
                        }
                        else
                        {
                            *(int *)value->real = tempReal;
                            *(int *)value->imaginary = tempImaginary;

                            matrix->data[i * matrix->length + j] = value;
                            validInput = 1;
                        }
                    }
                }
                break;
                default:
                    break;
                }
            }
        }
    }
    clearInputBuffer();
}

/// @brief AutoInitializing
/// @param matrix Matrix ptr
/// @param complexChoice variable shows, when matrix of complex, whether complex has INT or DOUBLE in it
//  0 - Not complex, 1 - DOUBLE in comeplx, 2 - INT
void setupMatrixElements(Matrix *matrix, int complexChoice)
{
    matrix->data = malloc(matrix->height * matrix->length * sizeof(void *));
    for (int i = 0; i < matrix->height * matrix->length; i++)
    {
        if (complexChoice != 0)
        {
            if (complexChoice == 1)
            {
                matrix->data[i] = matrix->typeInfo->allocate(DOUBLE);
            }
            else if (complexChoice == 2)
            {
                matrix->data[i] = matrix->typeInfo->allocate(INT);
            }
        }
        else if (complexChoice == 0)
        {
            matrix->data[i] = matrix->typeInfo->allocate(matrix->typeComponents);
        }
    }
}

void transportMatrix(Matrix *matrix)
{
    void **tempData = malloc(matrix->height * matrix->length * sizeof(void *));

    for (int i = 0; i < matrix->height * matrix->length; i++)
    {
        tempData[i] = matrix->data[i];
    }

    unsigned int oldHeight = matrix->height;
    matrix->height = matrix->length;
    matrix->length = oldHeight;

    // trasposition
    for (int i = 0; i < matrix->height; i++)
    {
        for (int j = 0; j < matrix->length; j++)
        {
            matrix->data[i * matrix->length + j] = tempData[j * matrix->height + i];
        }
    }

    free(tempData);
}

void freeMatrix(Matrix *matrix)
{
    for (int i = 0; i < matrix->height * matrix->length; i++)
    {
        matrix->typeInfo->Free(matrix->data[i]);
    }
    free(matrix->data);
    matrix->data = NULL;
    free(matrix);
}

void printMatrix(const Matrix *matrix)
{
    printf("\nMatrix %ux%u:\n", matrix->height, matrix->length);
    for (int i = 0; i < matrix->height; i++)
    {
        for (int j = 0; j < matrix->length; j++)
        {
            void *element = matrix->data[i * matrix->length + j];
            matrix->typeInfo->print(element);
        }
        printf("\n");
    }
    printf("\n");
}
