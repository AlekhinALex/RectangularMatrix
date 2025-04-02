#pragma once

#include "typeInfo.h"

typedef struct Matrix
{
    unsigned int length;
    unsigned int height;
    void *data;
    const struct typeInfo *typeInfo;
} Matrix;

enum isSuccess addMatrix(const Matrix *matrix1, const Matrix *matrix2, Matrix *result);
enum isSuccess multiplyMatrix(const Matrix *matrix1, const Matrix *matrix2, Matrix *result);
enum isSuccess readMatrixComponents(Matrix *matrix);
enum isSuccess transposeMatrix(Matrix *matrix);

// TODO: Доступ по индексу к эдементу на чтение и на запись

void printMatrix(const Matrix *matrix);
void removeInternal(Matrix *matrix);
