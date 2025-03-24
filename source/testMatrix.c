#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "../inc/complex.h"
#include "../inc/integer.h"
#include "../inc/double.h"
#include "../inc/complexImpl.h"
#include "../inc/integerImpl.h"
#include "../inc/doubleImpl.h"
#include "../inc/inputHandling.h"
#include "../inc/matrix.h"
#include "../inc/errorHandling.h"

static void fillIntMatrix(Matrix *m, const int *values)
{
    int *data = (int *)m->data;
    for (int i = 0; i < m->height * m->length; i++)
    {
        data[i] = values[i];
    }
}

static void fillDoubleMatrix(Matrix *m, const double *values)
{
    double *data = (double *)m->data;
    for (int i = 0; i < m->height * m->length; i++)
    {
        data[i] = values[i];
    }
}

static void fillComplexMatrix(Matrix *m, const Complex *values)
{
    Complex *data = (Complex *)m->data;
    for (int i = 0; i < m->height * m->length; i++)
    {
        data[i] = values[i];
    }
}

static int compareIntMatrices(const Matrix *m1, const Matrix *m2)
{
    if (m1->height != m2->height || m1->length != m2->length)
    {
        return 0;
    }
    int *data1 = (int *)m1->data;
    int *data2 = (int *)m2->data;
    for (int i = 0; i < m1->height * m1->length; i++)
    {
        if (data1[i] != data2[i])
        {
            return 0;
        }
    }
    return 1;
}

static int compareDoubleMatrices(const Matrix *m1, const Matrix *m2, double epsilon)
{
    if (m1->height != m2->height || m1->length != m2->length)
    {
        return 0;
    }
    double *data1 = (double *)m1->data;
    double *data2 = (double *)m2->data;
    for (int i = 0; i < m1->height * m1->length; i++)
    {
        if (fabs(data1[i] - data2[i]) > epsilon)
        {
            return 0;
        }
    }
    return 1;
}

static int compareComplexMatrices(const Matrix *m1, const Matrix *m2, double epsilon)
{
    if (m1->height != m2->height || m1->length != m2->length)
    {
        return 0;
    }
    Complex *data1 = (Complex *)m1->data;
    Complex *data2 = (Complex *)m2->data;
    for (int i = 0; i < m1->height * m1->length; i++)
    {
        if (fabs(data1[i].real - data2[i].real) > epsilon ||
            fabs(data1[i].imaginary - data2[i].imaginary) > epsilon)
        {
            return 0;
        }
    }
    return 1;
}

static void testIntegerOperations()
{
    // Addition test
    Matrix m1 = setupMatrix(2, 2, getTypeInfoInteger());
    Matrix m2 = setupMatrix(2, 2, getTypeInfoInteger());
    Matrix result = setupMatrix(2, 2, getTypeInfoInteger());

    int values1[] = {1, 2,
                     3, 4};

    int values2[] = {1, 1,
                     1, 1};

    int expected[] = {2, 3,
                      4, 5};

    fillIntMatrix(&m1, values1);
    fillIntMatrix(&m2, values2);

    assert(addMatrix(&m1, &m2, &result) == SUCCESSFUL_EXECUTION);

    Matrix expectedMatrix = setupMatrix(2, 2, getTypeInfoInteger());
    fillIntMatrix(&expectedMatrix, expected);

    assert(compareIntMatrices(&result, &expectedMatrix));

    // Multiplication test
    Matrix m3 = setupMatrix(2, 3, getTypeInfoInteger());
    Matrix m4 = setupMatrix(3, 2, getTypeInfoInteger());
    Matrix multResult = setupMatrix(2, 2, getTypeInfoInteger());

    int values3[] = {1, 2, 3,
                     4, 5, 6};

    int values4[] = {1, 2,
                     3, 4,
                     5, 6};

    int expectedMult[] = {22, 28,
                          49, 64};

    fillIntMatrix(&m3, values3);
    fillIntMatrix(&m4, values4);

    assert(multiplyMatrix(&m3, &m4, &multResult) == SUCCESSFUL_EXECUTION);

    Matrix expectedMultMatrix = setupMatrix(2, 2, getTypeInfoInteger());
    fillIntMatrix(&expectedMultMatrix, expectedMult);

    assert(compareIntMatrices(&multResult, &expectedMultMatrix));

    freeMatrix(&m1);
    freeMatrix(&m2);
    freeMatrix(&m3);
    freeMatrix(&m4);
    freeMatrix(&result);
    freeMatrix(&multResult);
    freeMatrix(&expectedMatrix);
    freeMatrix(&expectedMultMatrix);

    printf("  ===  Integer matrix operations passed!\n");
}

static void testComplexOperations()
{
    Matrix m1 = setupMatrix(2, 2, getTypeInfoComplex());
    Matrix m2 = setupMatrix(2, 2, getTypeInfoComplex());
    Matrix result = setupMatrix(2, 2, getTypeInfoComplex());

    Complex values1[] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};

    Complex values2[] = {{1, 1}, {1, 1}, {1, 1}, {1, 1}};

    Complex expected[] = {{2, 2}, {3, 3}, {4, 4}, {5, 5}};

    fillComplexMatrix(&m1, values1);
    fillComplexMatrix(&m2, values2);

    assert(addMatrix(&m1, &m2, &result) == SUCCESSFUL_EXECUTION);

    Matrix expectedMatrix = setupMatrix(2, 2, getTypeInfoComplex());
    fillComplexMatrix(&expectedMatrix, expected);

    assert(compareComplexMatrices(&result, &expectedMatrix, 1e-10));

    // Test complex multiplication
    Matrix m3 = setupMatrix(2, 2, getTypeInfoComplex());
    Matrix m4 = setupMatrix(2, 2, getTypeInfoComplex());
    Matrix multResult = setupMatrix(2, 2, getTypeInfoComplex());

    Complex values3[] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
    Complex values4[] = {{1, 0}, {0, 1}, {1, 1}, {2, 2}};
    Complex expectedResults[] = {{1, 5}, {-1, 9}, {3, 11}, {-3, 19}};

    fillComplexMatrix(&m3, values3);
    fillComplexMatrix(&m4, values4);

    assert(multiplyMatrix(&m3, &m4, &multResult) == SUCCESSFUL_EXECUTION);
    Matrix expectedMatrixMult = setupMatrix(2, 2, getTypeInfoComplex());
    fillComplexMatrix(&expectedMatrixMult, expectedResults);

    assert(compareComplexMatrices(&expectedMatrixMult, &multResult, 1e-10));

    freeMatrix(&m1);
    freeMatrix(&m2);
    freeMatrix(&m3);
    freeMatrix(&m4);
    freeMatrix(&result);
    freeMatrix(&multResult);
    freeMatrix(&expectedMatrix);
    freeMatrix(&expectedMatrixMult);

    printf("  ===  Complex matrix operations passed!\n");
}

static void testDoubleOperations()
{
    // Addition
    Matrix m1 = setupMatrix(2, 2, getTypeInfoDouble());
    Matrix m2 = setupMatrix(2, 2, getTypeInfoDouble());
    Matrix result = setupMatrix(2, 2, getTypeInfoDouble());

    double values1[] = {1.5, 2.7, 3.2, 4.8};
    double values2[] = {1.1, 1.1, 1.1, 1.1};
    double expected[] = {2.6, 3.8, 4.3, 5.9};

    fillDoubleMatrix(&m1, values1);
    fillDoubleMatrix(&m2, values2);

    assert(addMatrix(&m1, &m2, &result) == SUCCESSFUL_EXECUTION);

    Matrix expectedMatrix = setupMatrix(2, 2, getTypeInfoDouble());
    fillDoubleMatrix(&expectedMatrix, expected);

    assert(compareDoubleMatrices(&result, &expectedMatrix, 1e-10));

    // Multiplication
    Matrix m3 = setupMatrix(2, 3, getTypeInfoDouble());
    Matrix m4 = setupMatrix(3, 2, getTypeInfoDouble());
    Matrix multResult = setupMatrix(2, 2, getTypeInfoDouble());

    double values3[] = {1.5, 2.0, 3.5,
                        4.0, 5.5, 6.0};

    double values4[] = {1.5, 2.0,
                        3.0, 4.5,
                        5.5, 6.0};

    double expectedMult[] = {27.5, 33.0,
                             55.5, 68.75};

    fillDoubleMatrix(&m3, values3);
    fillDoubleMatrix(&m4, values4);

    assert(multiplyMatrix(&m3, &m4, &multResult) == SUCCESSFUL_EXECUTION);

    Matrix expectedMultMatrix = setupMatrix(2, 2, getTypeInfoDouble());
    fillDoubleMatrix(&expectedMultMatrix, expectedMult);

    assert(compareDoubleMatrices(&multResult, &expectedMultMatrix, 1e-10));

    // Transposition
    Matrix m5 = setupMatrix(2, 3, getTypeInfoDouble());
    double values5[] = {1.1, 2.2, 3.3,
                        4.4, 5.5, 6.6};

    double expectedTrans[] = {1.1, 4.4,
                              2.2, 5.5,
                              3.3, 6.6};

    fillDoubleMatrix(&m5, values5);

    assert(transposeMatrix(&m5) == SUCCESSFUL_EXECUTION);

    Matrix expectedTransMatrix = setupMatrix(3, 2, getTypeInfoDouble());

    fillDoubleMatrix(&expectedTransMatrix, expectedTrans);

    assert(compareDoubleMatrices(&m5, &expectedTransMatrix, 1));

    freeMatrix(&m1);
    freeMatrix(&m2);
    freeMatrix(&m3);
    freeMatrix(&m4);
    freeMatrix(&m5);
    freeMatrix(&result);
    freeMatrix(&multResult);
    freeMatrix(&expectedMatrix);
    freeMatrix(&expectedMultMatrix);
    freeMatrix(&expectedTransMatrix);

    printf("  ===  Double matrix operations all passed!\n");
}

static void testErrorCases()
{
    // Different types
    Matrix intMatrix = setupMatrix(2, 2, getTypeInfoInteger());
    Matrix doubleMatrix = setupMatrix(2, 2, getTypeInfoDouble());
    Matrix result = setupMatrix(2, 2, getTypeInfoInteger());

    assert(addMatrix(&intMatrix, &doubleMatrix, &result) == ERROR_OCCURRED);

    // Different dimensions
    Matrix m1 = setupMatrix(2, 3, getTypeInfoInteger());
    Matrix m2 = setupMatrix(2, 2, getTypeInfoInteger());

    assert(addMatrix(&m1, &m2, &result) == ERROR_OCCURRED);
    assert(multiplyMatrix(&m1, &m2, &result) == ERROR_OCCURRED);

    freeMatrix(&intMatrix);
    freeMatrix(&doubleMatrix);
    freeMatrix(&m1);
    freeMatrix(&m2);
    freeMatrix(&result);

    printf("  ===  Error cases passed!\n");
}

int main()
{
    printf("\n--- Starting Matrix Tests ---\n\n");

    testIntegerOperations();
    testDoubleOperations();
    testComplexOperations();
    testErrorCases();

    printf("\n\n--- All Tests Passed! ---\n\n");
    return 0;
}
