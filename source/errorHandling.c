#include <stdio.h>

#include "../inc/matrix.h"
#include "../inc/errorHandling.h"

bool isNullMatrix(const Matrix *matrix)
{
    if (!matrix)
    {
        printf("Error: matrix is NULL\n");
        return true;
    }
    return false;
}

bool areMatricesSameSize(const Matrix *matrix1, const Matrix *matrix2)
{

    if (isNullMatrix(matrix1) || isNullMatrix(matrix2))
    {
        return false;
    }
    if (matrix1->height != matrix2->height || matrix1->length != matrix2->length)
    {
        printf("Error: Matrices must have identical sizes (%ux%u and %ux%u)\n",
               matrix1->height, matrix1->length, matrix2->height, matrix2->length);
        return false;
    }
    return true;
}

bool areMatricesCompatibleForMultiplication(const Matrix *matrix1, const Matrix *matrix2)
{
    if (matrix1->length != matrix2->height)
    {
        printf("Error: Incompatible matrix dimensions for multiplication: %ux%u and %ux%u\n",
               matrix1->height, matrix1->length, matrix2->height, matrix2->length);
        return false;
    }
    return true;
}

bool haveMatchingTypes(const Matrix *matrix1, const Matrix *matrix2)
{
    if (isNullMatrix(matrix1) || isNullMatrix(matrix2))
    {
        return false;
    }

    if (matrix1->typeInfo != matrix2->typeInfo)
    {
        printf("Error: Matrices have different types\n");
        return false;
    }

    return true;
}