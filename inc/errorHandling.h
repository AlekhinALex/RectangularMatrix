#pragma once

/// @brief this file doesn't see matrix.h, here's fix
typedef struct Matrix Matrix;

typedef enum isSuccess
{
    ERROR_OCCURRED,
    SUCCESSFUL_EXECUTION
} isSuccess;

typedef enum errorTests
{
    PASSED,
    ERROR_DETECTED
} errorTests;

errorTests isNullMatrix(const Matrix *matrix);
errorTests areMatricesSameSize(const Matrix *matrix1, const Matrix *matrix2);
errorTests areMatricesCompatibleForMultiplication(const Matrix *matrix1, const Matrix *matrix2);
errorTests haveMatchingTypes(const Matrix *matrix1, const Matrix *matrix2);