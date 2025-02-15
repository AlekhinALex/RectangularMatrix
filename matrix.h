#pragma once
#include "complex.h"
typedef struct Matrix
{
    unsigned length;
    unsigned height;
    Complex *data;
} Matrix;

Matrix MatrixInput();
void MatrixOutput(Matrix matrix);