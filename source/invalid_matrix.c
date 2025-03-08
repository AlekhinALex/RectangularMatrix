#include <stdio.h>

#include "../inc/typeInfo.h"
#include "../inc/matrix.h"
#include "../inc/typeInfoMatrix.h"
#include "../inc/complex.h"
#include "../inc/double.h"
#include "../inc/integer.h"

void addMatrix(const void *a, const void *b, void *result)
{
    Matrix *matrix1 = (Matrix *)a;
    Matrix *matrix2 = (Matrix *)b;
    Matrix *resultMatrix = (Matrix *)result;

    if (matrix1->typeComponents != matrix2->typeComponents)
    {
        printf("Unable to sum different types.\n");
        return;
    }
    if (matrix1->typeComponents == INT)
    {
        const struct TypeInfo *intType = getTypeInfoInt();
        for (int i = 0; i < matrix1->height; i++)
        {
            for (int j = 0; j < matrix1->length; j++)
            {
                intType->add(matrix1->data[i * matrix1->length + j], matrix2->data[i * matrix1->length + j], resultMatrix->data[i * matrix1->length + j]);
            }
        }
    }
    else if (matrix1->typeComponents == DOUBLE)
    {
        const struct TypeInfo *doubleType = getTypeInfoDouble();
        for (int i = 0; i < matrix1->height; i++)
        {
            for (int j = 0; j < matrix1->length; j++)
            {
                doubleType->add(matrix1->data[i * matrix1->length + j], matrix2->data[i * matrix1->length + j], resultMatrix->data[i * matrix1->length + j]);
            }
        }
    }
    else if (matrix1->typeComponents == COMPLEX)
    {
        const struct TypeInfo *complexType = getTypeInfoComplex();
        for (int i = 0; i < matrix1->height; i++)
        {
            for (int j = 0; j < matrix1->length; j++)
            {
                complexType->add(matrix1->data[i * matrix1->length + j], matrix2->data[i * matrix1->length + j], resultMatrix->data[i * matrix1->length + j]);
            }
        }
    }
}

void *allocMatrix(datatype type)
{
    Matrix *newMatrix = malloc(sizeof(Matrix));
    newMatrix->height = 0;
    newMatrix->length = 0;
    if (type == INT)
    {
    }
    else if (type == COMPLEX)
    {
    }
}

void freeMatrix(Matrix *matrix)
{
    if (!matrix)
    {
        return;
    }

    if (matrix->data)
    {
        // Free each element
        for (unsigned int i = 0; i < matrix->height * matrix->length; i++)
        {
            if (matrix->data[i])
            {
                free((void *)matrix->data[i]);
            }
        }

        // Free the data array
        free((void *)matrix->data);
    }

    // Free the matrix structure
    free(matrix);
}

static struct TypeInfo *typeInfo = NULL;

const struct TypeInfo *getTypeInfoMatrix()
{
    if (typeInfo == NULL)
    {
        typeInfo = malloc(sizeof(struct TypeInfo));
        typeInfo->allocate = allocMatrix;
        // typeInfo->assign = assignMatrix;
        typeInfo->add = addMatrix;
        // typeInfo->substract = subMatrix;
        // typeInfo->multiply = multiplyMatrix;
        // typeInfo->print = printMatrix;
        typeInfo->Free = freeMatrix;
    }
    return typeInfo;
};