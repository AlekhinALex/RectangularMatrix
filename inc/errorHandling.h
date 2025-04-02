#pragma once

#include <stdbool.h>

/// @brief this file doesn't see matrix.h, here's fix
typedef struct Matrix Matrix;

// TODO bool_t + bool.h
// typedef enum errorTests
// {
//     PASSED,
//     ERROR_DETECTED
// } errorTests; //! bool

bool isNullMatrix(const Matrix *matrix);
bool areMatricesSameSize(const Matrix *matrix1, const Matrix *matrix2);
bool areMatricesCompatibleForMultiplication(const Matrix *matrix1, const Matrix *matrix2);
bool haveMatchingTypes(const Matrix *matrix1, const Matrix *matrix2);