#pragma once
#include <stdbool.h>
#include "matrix.h"

#ifdef __cplusplus
extern "C"
{
#endif
    bool isNullMatrix(const Matrix *matrix);
    bool areMatricesSameSize(const Matrix *matrix1, const Matrix *matrix2);
    bool areMatricesCompatibleForMultiplication(const Matrix *matrix1, const Matrix *matrix2);
    bool haveMatchingTypes(const Matrix *matrix1, const Matrix *matrix2);
#ifdef __cplusplus
}
#endif
