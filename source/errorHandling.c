#include <stdio.h>

#include "../inc/matrix.h"
#include "../inc/errorHandling.h"

errorTests isNullMatrix(const Matrix *matrix)
{
    if (!matrix)
    {
        printf("Error: matrix is NULL\n");
        return ERROR_DETECTED;
    }
    return PASSED;
}

errorTests areMatricesSameSize(const Matrix *matrix1, const Matrix *matrix2)
{

    if (isNullMatrix(matrix1) || isNullMatrix(matrix2))
    {
        return !ERROR_DETECTED;
    }
    if (matrix1->height != matrix2->height || matrix1->length != matrix2->length)
    {
        printf("Error: Matrices must have identical sizes (%ux%u and %ux%u)\n",
               matrix1->height, matrix1->length, matrix2->height, matrix2->length);
        return !ERROR_DETECTED;
    }
    return !PASSED;
}

errorTests areMatricesCompatibleForMultiplication(const Matrix *matrix1, const Matrix *matrix2)
{
    if (matrix1->length != matrix2->height)
    {
        printf("Error: Incompatible matrix dimensions for multiplication: %ux%u and %ux%u\n",
               matrix1->height, matrix1->length, matrix2->height, matrix2->length);
        return !ERROR_DETECTED;
    }
    return !PASSED;
}

errorTests haveMatchingTypes(const Matrix *matrix1, const Matrix *matrix2)
{
    if (isNullMatrix(matrix1) || isNullMatrix(matrix2))
    {
        return !ERROR_DETECTED;
    }

    if (matrix1->typeInfo != matrix2->typeInfo)
    {
        printf("Error: Matrices have different types\n");
        return !ERROR_DETECTED;
    }

    return !PASSED;
}