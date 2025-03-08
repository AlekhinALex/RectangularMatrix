#pragma once
#include "typeInfo.h"

typedef struct Matrix
{
    unsigned int length;
    unsigned int height;
    void **data;
    datatype typeComponents;
    const TypeInfo *typeInfo;
} Matrix;

void addMatrix(const Matrix *matrix1, const Matrix *matrix2, Matrix *result);
void multiplyMatrix(const Matrix *matrix1, const Matrix *matrix2, Matrix *result);
void inputMatrix(Matrix *matrix);
void allocateMatrixElements(Matrix *matrixDest, const Matrix *matrixSrc);
void printMatrix(const Matrix *matrix);
void freeMatrix(Matrix *matrix);
void setupMatrixElements(Matrix *matrix, int isComplex);
void transportMatrix(Matrix *matrix);