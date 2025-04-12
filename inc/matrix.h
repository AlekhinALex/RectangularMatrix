#pragma once

#include "typeInfo.h"

#ifdef __cplusplus
extern "C"
{
#endif

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
    enum isSuccess printMatrixElement(const Matrix *matrix, int x, int y);
    enum isSuccess readMatrixElement(Matrix *matrix, int x, int y);
    void createNewMatrix(unsigned int height, unsigned int length, const typeInfo *type, Matrix *matrix);
    void printMatrix(const Matrix *matrix);
    void removeInternal(Matrix *matrix); // cleanup

#ifdef __cplusplus
}
#endif
