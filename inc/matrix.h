#pragma once
#include "typeInfo.h"

typedef struct Matrix
{
    unsigned int length;
    unsigned int height;
    void **data;
    const TypeInfo *typeInfo;
} Matrix;

int addMatrix(const Matrix *matrix1, const Matrix *matrix2, Matrix *result);
int multiplyMatrix(const Matrix *matrix1, const Matrix *matrix2, Matrix *result);
int inputMatrix(Matrix *matrix);
int allocateMatrixElements(Matrix *matrixDest, const Matrix *matrixSrc);
void printMatrix(const Matrix *matrix);
void freeMatrix(Matrix *matrix);
void setupMatrixElements(Matrix *matrix);
int transportMatrix(Matrix *matrix);