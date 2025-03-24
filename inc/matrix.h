#pragma once
#include "typeInfo.h"

typedef struct Matrix
{
    unsigned int length;
    unsigned int height;
    void *data;
    const struct TypeInfo *typeInfo;
} Matrix;

enum isSuccess addMatrix(const Matrix *matrix1, const Matrix *matrix2, Matrix *result);
enum isSuccess multiplyMatrix(const Matrix *matrix1, const Matrix *matrix2, Matrix *result);
enum isSuccess inputNewMatrix(Matrix *matrix);
enum isSuccess transposeMatrix(Matrix *matrix);
void readMatrixComponents(Matrix *matrix);
void printMatrix(const Matrix *matrix);
void freeMatrix(Matrix *matrix);