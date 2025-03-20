#pragma once
#include "matrix.h"

#define ERROR_OCCURRED 0
#define SUCCESSFUL_EXECUTION 1

int isNullMatrix(const Matrix *matrix);
int areMatricesSameSize(const Matrix *matrix1, const Matrix *matrix2);
int areMatricesCompatibleForMultiplication(const Matrix *matrix1, const Matrix *matrix2);
int haveMatchingTypes(const Matrix *matrix1, const Matrix *matrix2);