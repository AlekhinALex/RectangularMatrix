#pragma once
#include "complex.h"
typedef struct Matrix
{
    unsigned int length;
    unsigned int height;
    Complex *data;
} Matrix;

Matrix MatrixInput();
void MatrixOutput(Matrix matrix);
void MatrixFree(Matrix *matrix);