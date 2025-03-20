#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../inc/typeInfo.h"
#include "../inc/errorHandling.h"
#include "../inc/inputHandling.h"

int addMatrix(const Matrix *matrix1, const Matrix *matrix2, Matrix *result)
{
    // error handling
    if (isNullMatrix(matrix1) || isNullMatrix(matrix2))
    {
        return ERROR_OCCURRED;
    }

    if (haveMatchingTypes(matrix1, matrix2))
    {
        return ERROR_OCCURRED;
    }

    if (areMatricesSameSize(matrix1, matrix2))
    {
        return ERROR_OCCURRED;
    }

    result->height = matrix1->height;
    result->length = matrix1->length;
    result->typeInfo = matrix1->typeInfo;

    if (allocateMatrixElements(result, matrix1) != SUCCESSFUL_EXECUTION)
    {
        return ERROR_OCCURRED;
    }

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

    return SUCCESSFUL_EXECUTION;
}

int multiplyMatrix(const Matrix *matrix1, const Matrix *matrix2, Matrix *result)
{
    // error handling
    if (isNullMatrix(matrix1) || isNullMatrix(matrix2))
    {
        return ERROR_OCCURRED;
    }

    if (haveMatchingTypes(matrix1, matrix2))
    {
        return ERROR_OCCURRED;
    }

    if (areMatricesSameSize(matrix1, matrix2))
    {
        return ERROR_OCCURRED;
    }

    result->height = matrix1->height;
    result->length = matrix2->length;
    result->typeInfo = matrix1->typeInfo;
    if (!allocateMatrixElements(result, matrix1))
    {
        return ERROR_OCCURRED;
    }
    printf("Hello\n");

    void *temp = NULL;
    temp = result->typeInfo->allocate();

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

    return SUCCESSFUL_EXECUTION;
}

int allocateMatrixElements(Matrix *matrixDest, const Matrix *matrixSrc)
{
    if (isNullMatrix(matrixSrc))
    {
        return ERROR_OCCURRED;
    }

    matrixDest->data = malloc(matrixDest->height * matrixDest->length * sizeof(void *));

    for (int i = 0; i < matrixDest->height * matrixDest->length; i++)
    {
        matrixDest->data[i] = matrixDest->typeInfo->allocate();
    }

    return SUCCESSFUL_EXECUTION;
}

int inputMatrix(Matrix *matrix)
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
        matrix->typeInfo = getTypeInfoDouble();
        break;
    case 2:
        matrix->typeInfo = getTypeInfoInt();
        break;
    case 3:
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

    printf("Input rules:\n");
    switch (typeHolder)
    {
    case 1:
        printf("Enter real numbers (e.g., 5.2)\n");
        break;
    case 2:
        printf("Enter integer numbers (e.g., 5)\n");
        break;
    case 3:
        printf("Enter complex numbers (e.g., (5, 3) or (3.6, 9) )\n");
        break;
    default:
        break;
    }

    setupMatrixElements(matrix);

    for (int i = 0; i < matrix->height; i++)
    {
        for (int j = 0; j < matrix->length; j++)
        {
            int validInput = 0;
            while (!validInput)
            {

                void *element = matrix->typeInfo->input();
                if (element == NULL)
                {
                    invalidInput();
                    clearInputBuffer();
                }
                else
                {
                    matrix->data[i * matrix->length + j] = element;
                    validInput = 1;
                }
            }
        }
    }

    clearInputBuffer();

    return SUCCESSFUL_EXECUTION;
}

void setupMatrixElements(Matrix *matrix)
{
    matrix->data = malloc(matrix->height * matrix->length * sizeof(void *));

    for (int i = 0; i < matrix->height * matrix->length; i++)
    {
        matrix->data[i] = matrix->typeInfo->allocate();
    }
}

int transportMatrix(Matrix *matrix)
{
    if (isNullMatrix(matrix))
    {
        return ERROR_OCCURRED;
    }

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

    return SUCCESSFUL_EXECUTION;
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
