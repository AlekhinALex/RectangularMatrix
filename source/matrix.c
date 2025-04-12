#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../inc/inputHandling.h"
#include "../inc/errorHandling.h"

isSuccess addMatrix(const Matrix *matrix1, const Matrix *matrix2, Matrix *result)
{
    if (isNullMatrix(matrix1) ||
        isNullMatrix(matrix2) ||
        isNullMatrix(result))
    {
        return ERROR_OCCURRED;
    }

    if (!haveMatchingTypes(matrix1, matrix2) ||
        !areMatricesSameSize(matrix1, matrix2) ||
        !haveMatchingTypes(matrix1, result) ||
        !areMatricesSameSize(matrix1, result))
    {
        return ERROR_OCCURRED;
    }

    size_t elementSize = matrix1->typeInfo->size();
    unsigned int totalElements = matrix1->height * matrix1->length;

    char *ptr1 = (char *)matrix1->data;
    char *ptr2 = (char *)matrix2->data;
    char *ptrResult = (char *)result->data;

    for (unsigned int i = 0; i < totalElements; i++)
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
    if (isNullMatrix(matrix1) ||
        isNullMatrix(matrix2) ||
        isNullMatrix(result))
    {
        return ERROR_OCCURRED;
    }

    if (!haveMatchingTypes(matrix1, matrix2) ||
        !haveMatchingTypes(matrix1, result))
    {
        return ERROR_OCCURRED;
    }

    if (matrix1->length != matrix2->height)
    {
        return ERROR_OCCURRED;
    }

    void *temp = malloc(result->typeInfo->size());

    size_t elementSize = result->typeInfo->size();

    char *ptrMatrix1 = (char *)matrix1->data;
    char *ptrMatrix2 = (char *)matrix2->data;
    char *ptrResult = (char *)result->data;

    // Matrix multiplication
    for (unsigned int i = 0; i < matrix1->height; i++)
    {
        for (unsigned int j = 0; j < matrix2->length; j++)
        {
            for (unsigned int k = 0; k < matrix1->length; k++)
            {
                const void *elemA = ptrMatrix1 + (i * matrix1->length + k) * elementSize;
                const void *elemB = ptrMatrix2 + (k * matrix2->length + j) * elementSize;
                void *elemResult = ptrResult + (i * result->length + j) * elementSize;

                result->typeInfo->multiply(elemA, elemB, temp);
                result->typeInfo->add(elemResult, temp, elemResult);
            }
        }
    }

    free(temp);
    return SUCCESSFUL_EXECUTION;
}

isSuccess readMatrixComponents(Matrix *matrix)
{
    printf("\nEnter matrix: %ux%u\n", matrix->height, matrix->length);
    printf("---\n");

    size_t elementSize = matrix->typeInfo->size();
    unsigned int totalElements = matrix->height * matrix->length;
    char *currentElement = (char *)matrix->data;

    for (unsigned int i = 0; i < totalElements; i++)
    {
        while (matrix->typeInfo->input(currentElement) != SUCCESSFUL_EXECUTION)
        {
        }
        currentElement += elementSize;
    }

    //? Should I keep it here?
    printMatrix(matrix);

    return SUCCESSFUL_EXECUTION;
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

    matrix->height = oldLength;
    matrix->length = oldHeight;

    // Transposition
    for (unsigned int i = 0; i < oldHeight; i++)
    {
        for (unsigned int j = 0; j < i; j++)
        {
            void *element1 = (char *)matrix->data + (i * oldLength + j) * elementSize;
            void *element2 = (char *)matrix->data + (j * oldHeight + i) * elementSize;

            matrix->typeInfo->swap(element1, element2);
        }
    }

    return SUCCESSFUL_EXECUTION;
}
void removeInternal(Matrix *matrix)
{
    free(matrix->data);
}

isSuccess printMatrixElement(const Matrix *matrix, int row, int colomn)
{
    if (isNullMatrix(matrix))
    {
        return ERROR_OCCURRED;
    }
    row--;
    colomn--;
    size_t elementSize = matrix->typeInfo->size();
    void *element = (void *)((char *)matrix->data + (row * matrix->length + colomn) * elementSize);
    matrix->typeInfo->print(element);

    return SUCCESSFUL_EXECUTION;
}

isSuccess readMatrixElement(Matrix *matrix, int row, int colomn)
{
    if (isNullMatrix(matrix))
    {
        return ERROR_OCCURRED;
    }

    size_t elementSize = matrix->typeInfo->size();
    void *element1 = (void *)((char *)matrix->data + (row * matrix->length + colomn) * elementSize);
    isSuccess status;
    while (1)
    {
        status = matrix->typeInfo->input(element1);

        if (status == SUCCESSFUL_EXECUTION)
        {
            break;
        }
    }

    return SUCCESSFUL_EXECUTION;
}

void createNewMatrix(unsigned int height, unsigned int length, const typeInfo *type, Matrix *matrix)
{
    matrix->height = height;
    matrix->length = length;
    matrix->typeInfo = type;
    matrix->data = malloc(matrix->height * matrix->length * matrix->typeInfo->size());
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
