#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../inc/inputHandling.h"

isSuccess addMatrix(const Matrix *matrix1, const Matrix *matrix2, Matrix *result)
{
    if (isNullMatrix(matrix1) || isNullMatrix(matrix2))
    {
        return ERROR_OCCURRED;
    }

    if (!haveMatchingTypes(matrix1, matrix2) || !areMatricesSameSize(matrix1, matrix2))
    {
        return ERROR_OCCURRED;
    }

    *result = setupMatrix(matrix1->height, matrix1->length, matrix1->typeInfo);

    size_t elementSize = matrix1->typeInfo->size();
    size_t totalElements = matrix1->height * matrix1->length;

    char *ptr1 = matrix1->data;
    char *ptr2 = matrix2->data;
    char *ptrResult = result->data;

    for (size_t i = 0; i < totalElements; i++)
    {
        result->typeInfo->add(ptr1, ptr2, ptrResult);
        ptr1 += elementSize;
        ptr2 += elementSize;
        ptrResult += elementSize;
    }

    return SUCCESSFUL_EXECUTION;
}

isSuccess multiplyMatrix(const Matrix *matrix1, const Matrix *matrix2, Matrix *result)
{
    if (isNullMatrix(matrix1) || isNullMatrix(matrix2))
    {
        return ERROR_OCCURRED;
    }

    if (!haveMatchingTypes(matrix1, matrix2))
    {
        return ERROR_OCCURRED;
    }

    if (matrix1->length != matrix2->height)
    {
        return ERROR_OCCURRED;
    }

    // Constructor
    *result = setupMatrix(matrix1->height, matrix2->length, matrix1->typeInfo);

    void *temp = malloc(result->typeInfo->size());

    size_t elementSize = result->typeInfo->size();

    char *ptr1 = matrix1->data;
    char *ptr2 = matrix2->data;
    char *ptrResult = result->data;

    // Matrix multiplication
    for (size_t i = 0; i < matrix1->height; i++)
    {
        for (size_t j = 0; j < matrix2->length; j++)
        {
            for (size_t k = 0; k < matrix1->length; k++)
            {
                const void *elemA = ptr1 + (i * matrix1->length + k) * elementSize;
                const void *elemB = ptr2 + (k * matrix2->length + j) * elementSize;
                void *elemResult = ptrResult + (i * result->length + j) * elementSize;

                result->typeInfo->multiply(elemA, elemB, temp);
                result->typeInfo->add(elemResult, temp, elemResult);
            }
        }
    }

    free(temp);
    return SUCCESSFUL_EXECUTION;
}

isSuccess inputNewMatrix(Matrix *matrix)
{
    int typeHolder = 0;
    unsigned int height, length;
    printf("Enter what types of data will be stored in the matrix:\n");
    printf("1) Real numbers\n");
    printf("2) Integers\n");
    printf("3) Complex numbers\n");
    typeHolder = getChoice(1, 3);

    printf("\nMatrix Size\n");
    printf("-----------\n");
    printf("Remember, the matrix dimensions must be greater than zero.\n");

    printf("Enter matrix height: ");
    height = inputDimension();

    printf("Enter matrix length: ");
    length = inputDimension();

    // Constructor
    *matrix = createNewMatrix(height, length, typeHolder);

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

    // Reading values
    readMatrixComponents(matrix);

    clearInputBuffer();

    return SUCCESSFUL_EXECUTION;
}

void readMatrixComponents(Matrix *matrix)
{
    size_t elementSize = matrix->typeInfo->size();
    size_t totalElements = matrix->height * matrix->length;
    void *currentElement = matrix->data;

    for (size_t i = 0; i < totalElements; i++)
    {
        while (1)
        {
            if (matrix->typeInfo->input(currentElement) == SUCCESSFUL_EXECUTION)
            {
                break;
            }

            invalidInput();
            clearInputBuffer();
        }

        currentElement += elementSize;
    }
}

isSuccess transposeMatrix(Matrix *matrix)
{
    if (isNullMatrix(matrix))
    {
        return ERROR_OCCURRED;
    }

    unsigned int oldHeight = matrix->height;
    unsigned int oldLength = matrix->length;
    size_t totalElements = matrix->height * matrix->length;
    size_t elementSize = matrix->typeInfo->size();

    void *tempData = malloc(totalElements * elementSize);

    void *src = matrix->data;
    void *dst = tempData;
    for (size_t i = 0; i < totalElements; i++)
    {
        matrix->typeInfo->assign(dst, src);
        src += elementSize;
        dst += elementSize;
    }

    matrix->height = oldLength;
    matrix->length = oldHeight;

    // Transposition
    for (size_t i = 0; i < oldHeight; i++)
    {
        for (size_t j = 0; j < oldLength; j++)
        {
            // B[i][j] = A[j][i];
            void *srcElement = tempData + (i * oldLength + j) * elementSize;
            void *dstElement = matrix->data + (j * oldHeight + i) * elementSize;
            matrix->typeInfo->assign(dstElement, srcElement);
        }
    }

    free(tempData);
    return SUCCESSFUL_EXECUTION;
}

void freeMatrix(Matrix *matrix)
{
    free(matrix->data);
}

void printMatrix(const Matrix *matrix)
{
    printf("\nMatrix %ux%u:\n", matrix->height, matrix->length);
    char *currentElement = matrix->data;
    size_t elementSize = matrix->typeInfo->size();

    for (size_t i = 0; i < matrix->height; i++)
    {
        for (size_t j = 0; j < matrix->length; j++)
        {
            matrix->typeInfo->print(currentElement);
            currentElement += elementSize;
        }
        printf("\n");
    }
    printf("\n");
}
