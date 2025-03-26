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
    unsigned int totalElements = matrix1->height * matrix1->length;

    char *ptr1 = (char *)matrix1->data;
    char *ptr2 = (char *)matrix2->data;
    char *ptrResult = (char *)result->data;

    for (unsigned int i = 0; i < totalElements; i++)
    {
        result->typeInfo->add((const void *)ptr1, (const void *)ptr2, (void *)ptrResult);
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

    char *ptr1 = (char *)matrix1->data;
    char *ptr2 = (char *)matrix2->data;
    char *ptrResult = (char *)result->data;

    // Matrix multiplication
    for (unsigned int i = 0; i < matrix1->height; i++)
    {
        for (unsigned int j = 0; j < matrix2->length; j++)
        {
            for (unsigned int k = 0; k < matrix1->length; k++)
            {
                const void *elemA = (const void *)(ptr1 + (i * matrix1->length + k) * elementSize);
                const void *elemB = (const void *)(ptr2 + (k * matrix2->length + j) * elementSize);
                void *elemResult = (void *)(ptrResult + (i * result->length + j) * elementSize);

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
    unsigned int totalElements = matrix->height * matrix->length;
    char *currentElement = (char *)matrix->data;

    for (unsigned int i = 0; i < totalElements; i++)
    {
        while (1)
        {
            if (matrix->typeInfo->input((void *)currentElement) == SUCCESSFUL_EXECUTION)
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
    unsigned int totalElements = matrix->height * matrix->length;
    size_t elementSize = matrix->typeInfo->size();

    void *tempData = malloc(totalElements * elementSize);

    char *src = matrix->data;
    char *dst = tempData;
    for (unsigned int i = 0; i < totalElements; i++)
    {
        matrix->typeInfo->assign((void *)dst, (const void *)src);
        src += elementSize;
        dst += elementSize;
    }

    matrix->height = oldLength;
    matrix->length = oldHeight;

    // Transposition
    for (unsigned int i = 0; i < oldHeight; i++)
    {
        for (unsigned int j = 0; j < oldLength; j++)
        {
            // B[i][j] = A[j][i];
            void *srcElement = (void *)((char *)tempData + (i * oldLength + j) * elementSize);
            void *dstElement = (void *)((char *)matrix->data + (j * oldHeight + i) * elementSize);
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

    for (unsigned int i = 0; i < matrix->height; i++)
    {
        for (unsigned int j = 0; j < matrix->length; j++)
        {
            matrix->typeInfo->print((void *)currentElement);
            currentElement += elementSize;
        }
        printf("\n");
    }
    printf("\n");
}
