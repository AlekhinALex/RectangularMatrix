#include <stdio.h>

#include "../inc/matrix.h"
#include "../inc/errorHandling.h"

#define ERROR_DETECTED 1
#define PASSED 0

int isNullMatrix(const Matrix *matrix)
{
    if (!matrix)
    {
        printf("Error: matrix is NULL\n");
        return ERROR_DETECTED;
    }
    return PASSED;
}

int areMatricesSameSize(const Matrix *matrix1, const Matrix *matrix2)
{
    if (matrix1->height != matrix2->height || matrix1->length != matrix2->length)
    {
        printf("Error: Matrices must have identical sizes (%ux%u and %ux%u)\n",
               matrix1->height, matrix1->length, matrix2->height, matrix2->length);
        return ERROR_DETECTED;
    }
    return PASSED;
}

int areMatricesCompatibleForMultiplication(const Matrix *matrix1, const Matrix *matrix2)
{
    if (matrix1->length != matrix2->height)
    {
        printf("Error: Incompatible matrix dimensions for multiplication: %ux%u and %ux%u\n",
               matrix1->height, matrix1->length, matrix2->height, matrix2->length);
        return ERROR_DETECTED;
    }
    return PASSED;
}

int areMatricesCompatibleTypes(const Matrix *matrix1, const Matrix *matrix2)
{
    if (matrix1->typeComponents != matrix2->typeComponents)
    {
        printf("Error: Matrices must have identical types. Try again.\n");
        return ERROR_DETECTED;
    }
    return PASSED;
}