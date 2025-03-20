#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "../inc/errorHandling.h"
#include "../inc/typeInfoComplex.h"
#include "../inc/typeInfoDouble.h"
#include "../inc/typeInfoInteger.h"
#include "../inc/typeInfo.h"
#include "../inc/matrix.h"

Matrix *createTestMatrix(int height, int length, const TypeInfo *type)
{
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->height = height;
    matrix->length = length;
    matrix->typeInfo = type;
    setupMatrixElements(matrix);
    return matrix;
}

void testDoubleMatrixOperations()
{
    Matrix *matrix1 = createTestMatrix(2, 3, getTypeInfoDouble());
    Matrix *matrix2 = createTestMatrix(2, 3, getTypeInfoDouble());
    Matrix *result = createTestMatrix(2, 3, getTypeInfoDouble());

    for (int i = 0; i < matrix1->height; i++)
    {
        for (int j = 0; j < matrix1->length; j++)
        {
            double *val1 = matrix1->data[i * matrix1->length + j];
            double *val2 = matrix2->data[i * matrix2->length + j];
            *val1 = i + j + 1.0;
            *val2 = 1.0;
        }
    }

    assert(addMatrix(matrix1, matrix2, result) == SUCCESSFUL_EXECUTION);

    for (int i = 0; i < result->height; i++)
    {
        for (int j = 0; j < result->length; j++)
        {
            double *res = result->data[i * result->length + j];
            assert(fabs(*res - ((i + j + 1.0) + 1.0)) < 1e-10);
        }
    }

    assert(transportMatrix(matrix1) == SUCCESSFUL_EXECUTION);
    assert(matrix1->height == 3 && matrix1->length == 2);

    freeMatrix(matrix1);
    freeMatrix(matrix2);
    freeMatrix(result);
    printf(" -- Double matrix operations passed!\n");
}

void testTypeMatching()
{
    // (Double)
    Matrix *matrix1 = createTestMatrix(2, 2, getTypeInfoDouble());
    Matrix *matrix2 = createTestMatrix(2, 2, getTypeInfoDouble());
    assert(haveMatchingTypes(matrix1, matrix2) == 0);

    // (Double vs Complex)
    Matrix *matrix3 = createTestMatrix(2, 2, getTypeInfoComplex());
    assert(haveMatchingTypes(matrix1, matrix3) == 1);

    // NULL matrix tests
    assert(haveMatchingTypes(NULL, matrix2) == 1);
    assert(haveMatchingTypes(matrix1, NULL) == 1);
    assert(haveMatchingTypes(NULL, NULL) == 1);

    freeMatrix(matrix1);
    freeMatrix(matrix2);
    freeMatrix(matrix3);

    printf(" -- Type matching tests passed!\n");
}

void testLargeMatrices()
{
    const int SIZE = 1000;

    Matrix *largeMatrix1 = createTestMatrix(SIZE, SIZE, getTypeInfoDouble());
    Matrix *largeMatrix2 = createTestMatrix(SIZE, SIZE, getTypeInfoDouble());
    Matrix *result = createTestMatrix(SIZE, SIZE, getTypeInfoDouble());

    for (int i = 0; i < SIZE * SIZE; i++)
    {
        double *val1 = largeMatrix1->data[i];
        double *val2 = largeMatrix2->data[i];
        *val1 = (double)(i % 100) / 10.0;
        *val2 = 1.0;
    }

    assert(addMatrix(largeMatrix1, largeMatrix2, result) == SUCCESSFUL_EXECUTION);

    for (int i = 0; i < 100; i++)
    {
        double *res = result->data[i];
        double *val1 = largeMatrix1->data[i];
        double *val2 = largeMatrix2->data[i];
        assert(fabs(*res - (*val1 + *val2)) < 1e-10);
    }

    // matrix multiplication (100x100 subset)
    Matrix *multMatrix1 = createTestMatrix(100, 100, getTypeInfoDouble());
    Matrix *multMatrix2 = createTestMatrix(100, 100, getTypeInfoDouble());
    Matrix *multResult = createTestMatrix(100, 100, getTypeInfoDouble());

    for (int i = 0; i < 100 * 100; i++)
    {
        double *val1 = multMatrix1->data[i];
        double *val2 = multMatrix2->data[i];
        *val1 = 1.0;
        *val2 = 2.0;
    }

    assert(multiplyMatrix(multMatrix1, multMatrix2, multResult) == SUCCESSFUL_EXECUTION);

    // Testing array of matricies
    const int NUM_MATRICES = 5;
    Matrix *matrices[NUM_MATRICES];

    for (int i = 0; i < NUM_MATRICES; i++)
    {
        matrices[i] = createTestMatrix(SIZE, SIZE, getTypeInfoDouble());
        for (int j = 0; j < SIZE * SIZE; j++)
        {
            double *val = matrices[i]->data[j];
            *val = (double)j;
        }
    }

    assert(transportMatrix(largeMatrix1) == SUCCESSFUL_EXECUTION);

    assert(haveMatchingTypes(largeMatrix1, largeMatrix2) == 0);

    freeMatrix(largeMatrix1);
    freeMatrix(largeMatrix2);
    freeMatrix(result);
    freeMatrix(multMatrix1);
    freeMatrix(multMatrix2);
    freeMatrix(multResult);

    for (int i = 0; i < NUM_MATRICES; i++)
    {
        freeMatrix(matrices[i]);
    }

    printf(" -- Large matrix tests passed!\n\n");
}

void testComplexMatrixOperations()
{
    Matrix *matrix1 = createTestMatrix(2, 2, getTypeInfoComplex());
    Matrix *matrix2 = createTestMatrix(2, 2, getTypeInfoComplex());
    Matrix *result = createTestMatrix(2, 2, getTypeInfoComplex());

    for (int i = 0; i < 4; i++)
    {
        Complex *c1 = matrix1->data[i];
        Complex *c2 = matrix2->data[i];

        c1->real = i + 1.0;
        c1->imaginary = i + 2.0;
        c2->real = 1.0;
        c2->imaginary = 1.0;
    }

    assert(addMatrix(matrix1, matrix2, result) == SUCCESSFUL_EXECUTION);

    for (int i = 0; i < 4; i++)
    {
        Complex *res = result->data[i];
        Complex *m1 = matrix1->data[i];
        Complex *m2 = matrix2->data[i];

        assert(fabs(res->real - (m1->real + m2->real)) < 1e-10);
        assert(fabs(res->imaginary - (m1->imaginary + m2->imaginary)) < 1e-10);
    }

    Matrix *multResult = createTestMatrix(2, 2, getTypeInfoComplex());
    assert(multiplyMatrix(matrix1, matrix2, multResult) == SUCCESSFUL_EXECUTION);

    freeMatrix(matrix1);
    freeMatrix(matrix2);
    freeMatrix(result);
    freeMatrix(multResult);
    printf(" -- Complex matrix operations passed!\n");
}

void testMatrixErrorHandling()
{
    // Test null matrix handling
    Matrix *matrix1 = NULL;
    Matrix *matrix2 = createTestMatrix(2, 2, getTypeInfoDouble());
    Matrix *result = createTestMatrix(2, 2, getTypeInfoDouble());

    assert(addMatrix(matrix1, matrix2, result) == ERROR_OCCURRED);
    assert(multiplyMatrix(matrix1, matrix2, result) == ERROR_OCCURRED);
    assert(transportMatrix(matrix1) == ERROR_OCCURRED);

    // Test incompatible matrix sizes for addition
    matrix1 = createTestMatrix(2, 3, getTypeInfoDouble());
    assert(addMatrix(matrix1, matrix2, result) == ERROR_OCCURRED);

    // Test incompatible matrix sizes for multiplication
    Matrix *matrix3 = createTestMatrix(3, 2, getTypeInfoDouble());
    assert(multiplyMatrix(matrix1, matrix3, result) == ERROR_OCCURRED);

    freeMatrix(matrix1);
    freeMatrix(matrix2);
    freeMatrix(matrix3);
    freeMatrix(result);
    printf(" -- Matrix error handling tests passed!\n");
}

int main()
{
    printf("\n=== Starting matrix tests ===\n\n");

    testTypeMatching();
    testDoubleMatrixOperations();
    testComplexMatrixOperations();
    testMatrixErrorHandling();
    testTypeMatching();
    testLargeMatrices();

    printf("\n\n=== All tests passed successfully! ===\n\n");
    return 0;
}
