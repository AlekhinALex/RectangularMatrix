#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>

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
    memcpy(m->data, values, m->height * m->length * sizeof(int));
}

static void fillDoubleMatrix(Matrix *m, const double *values)
{
    memcpy(m->data, values, m->height * m->length * sizeof(double));
}

static void fillComplexMatrix(Matrix *m, const Complex *values)
{
    memcpy(m->data, values, m->height * m->length * sizeof(Complex));
}

static int compareIntMatrices(const Matrix *m1, const Matrix *m2)
{
    if (m1->height != m2->height || m1->length != m2->length)
        return 0;

    int *data1 = (int *)m1->data;
    int *data2 = (int *)m2->data;
    for (int i = 0; i < m1->height * m1->length; i++)
    {
        if (data1[i] != data2[i])
            return 0;
    }
    return 1;
}

static int compareDoubleMatrices(const Matrix *m1, const Matrix *m2, double epsilon)
{
    if (m1->height != m2->height || m1->length != m2->length)
        return 0;

    double *data1 = (double *)m1->data;
    double *data2 = (double *)m2->data;
    for (int i = 0; i < m1->height * m1->length; i++)
    {
        if (fabs(data1[i] - data2[i]) > epsilon)
            return 0;
    }
    return 1;
}

static int compareComplexMatrices(const Matrix *m1, const Matrix *m2, double epsilon)
{
    if (m1->height != m2->height || m1->length != m2->length)
        return 0;

    Complex *data1 = (Complex *)m1->data;
    Complex *data2 = (Complex *)m2->data;
    for (int i = 0; i < m1->height * m1->length; i++)
    {
        if (fabs(data1[i].real - data2[i].real) > epsilon ||
            fabs(data1[i].imaginary - data2[i].imaginary) > epsilon)
            return 0;
    }
    return 1;
}

static void testIntegerOperations()
{
    // Test matrix addition
    Matrix m1;
    createNewMatrix(2, 2, getTypeInfoInteger(), &m1);
    Matrix m2;
    createNewMatrix(2, 2, getTypeInfoInteger(), &m2);
    Matrix result;
    createNewMatrix(2, 2, getTypeInfoInteger(), &result);

    int values1[] = {1, 2,
                     3, 4};

    int values2[] = {5, 6,
                     7, 8};

    int expectedAdd[] = {6, 8,
                         10, 12};

    fillIntMatrix(&m1, values1);
    fillIntMatrix(&m2, values2);

    assert(addMatrix(&m1, &m2, &result) == SUCCESSFUL_EXECUTION);

    Matrix expectedMatrix;
    createNewMatrix(2, 2, getTypeInfoInteger(), &expectedMatrix);
    fillIntMatrix(&expectedMatrix, expectedAdd);
    assert(compareIntMatrices(&result, &expectedMatrix));

    // Test matrix multiplication
    Matrix m3;
    createNewMatrix(2, 3, getTypeInfoInteger(), &m3);
    Matrix m4;
    createNewMatrix(3, 2, getTypeInfoInteger(), &m4);
    Matrix multResult;
    createNewMatrix(2, 2, getTypeInfoInteger(), &multResult);

    int values3[] = {1, 2, 3,
                     4, 5, 6};

    int values4[] = {7, 8,
                     9, 10,
                     11, 12};

    int expectedMult[] = {58, 64,
                          139, 154};

    fillIntMatrix(&m3, values3);
    fillIntMatrix(&m4, values4);

    assert(multiplyMatrix(&m3, &m4, &multResult) == SUCCESSFUL_EXECUTION);

    Matrix expectedMultMatrix;
    createNewMatrix(2, 2, getTypeInfoInteger(), &expectedMultMatrix);
    fillIntMatrix(&expectedMultMatrix, expectedMult);
    assert(compareIntMatrices(&multResult, &expectedMultMatrix));

    removeInternal(&m1);
    removeInternal(&m2);
    removeInternal(&m3);
    removeInternal(&m4);
    removeInternal(&result);
    removeInternal(&multResult);
    removeInternal(&expectedMatrix);
    removeInternal(&expectedMultMatrix);

    printf("  === Integer matrix operations passed!\n");
}

static void testDoubleOperations()
{
    // Test matrix addition
    Matrix m1;
    createNewMatrix(2, 2, getTypeInfoDouble(), &m1);
    Matrix m2;
    createNewMatrix(2, 2, getTypeInfoDouble(), &m2);
    Matrix result;
    createNewMatrix(2, 2, getTypeInfoDouble(), &result);

    double values1[] = {1.5, 2.5,
                        3.5, 4.5};

    double values2[] = {0.5, 1.5,
                        2.5, 3.5};

    double expectedAdd[] = {2.0, 4.0,
                            6.0, 8.0};

    fillDoubleMatrix(&m1, values1);
    fillDoubleMatrix(&m2, values2);

    assert(addMatrix(&m1, &m2, &result) == SUCCESSFUL_EXECUTION);

    Matrix expectedMatrix;
    createNewMatrix(2, 2, getTypeInfoDouble(), &expectedMatrix);
    fillDoubleMatrix(&expectedMatrix, expectedAdd);
    assert(compareDoubleMatrices(&result, &expectedMatrix, 1e-10));

    // Test matrix multiplication
    Matrix m3;
    createNewMatrix(2, 3, getTypeInfoDouble(), &m3);
    Matrix m4;
    createNewMatrix(3, 2, getTypeInfoDouble(), &m4);
    Matrix multResult;
    createNewMatrix(2, 2, getTypeInfoDouble(), &multResult);

    double values3[] = {1.5, 2.0, 2.5,
                        3.0, 3.5, 4.0};

    double values4[] = {1.0, 1.5,
                        2.0, 2.5,
                        3.0, 3.5};

    double expectedMult[] = {13.0, 16,
                             22.0, 27.25};

    fillDoubleMatrix(&m3, values3);
    fillDoubleMatrix(&m4, values4);

    assert(multiplyMatrix(&m3, &m4, &multResult) == SUCCESSFUL_EXECUTION);

    Matrix expectedMultMatrix;
    createNewMatrix(2, 2, getTypeInfoDouble(), &expectedMultMatrix);
    fillDoubleMatrix(&expectedMultMatrix, expectedMult);
    assert(compareDoubleMatrices(&multResult, &expectedMultMatrix, 1e-10));

    removeInternal(&m1);
    removeInternal(&m2);
    removeInternal(&m3);
    removeInternal(&m4);
    removeInternal(&result);
    removeInternal(&multResult);
    removeInternal(&expectedMatrix);
    removeInternal(&expectedMultMatrix);

    printf("  === Double matrix operations passed!\n");
}

static void testComplexOperations()
{
    // Test matrix addition
    Matrix m1;
    createNewMatrix(2, 2, getTypeInfoComplex(), &m1);
    Matrix m2;
    createNewMatrix(2, 2, getTypeInfoComplex(), &m2);
    Matrix result;
    createNewMatrix(2, 2, getTypeInfoComplex(), &result);

    Complex values1[] = {{1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}, {4.0, 4.0}};
    Complex values2[] = {{0.5, 0.5}, {1.5, 1.5}, {2.5, 2.5}, {3.5, 3.5}};
    Complex expectedAdd[] = {{1.5, 1.5}, {3.5, 3.5}, {5.5, 5.5}, {7.5, 7.5}};

    fillComplexMatrix(&m1, values1);
    fillComplexMatrix(&m2, values2);

    assert(addMatrix(&m1, &m2, &result) == SUCCESSFUL_EXECUTION);

    Matrix expectedMatrix;
    createNewMatrix(2, 2, getTypeInfoComplex(), &expectedMatrix);
    fillComplexMatrix(&expectedMatrix, expectedAdd);
    assert(compareComplexMatrices(&result, &expectedMatrix, 1e-10));

    // Test matrix multiplication
    Matrix m3;
    createNewMatrix(2, 2, getTypeInfoComplex(), &m3);
    Matrix m4;
    createNewMatrix(2, 2, getTypeInfoComplex(), &m4);
    Matrix multResult;
    createNewMatrix(2, 2, getTypeInfoComplex(), &multResult);

    Complex values3[] = {{1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}, {4.0, 4.0}};
    Complex values4[] = {{1.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {2.0, 2.0}};

    fillComplexMatrix(&m3, values3);
    fillComplexMatrix(&m4, values4);

    assert(multiplyMatrix(&m3, &m4, &multResult) == SUCCESSFUL_EXECUTION);

    removeInternal(&m1);
    removeInternal(&m2);
    removeInternal(&m3);
    removeInternal(&m4);
    removeInternal(&result);
    removeInternal(&multResult);
    removeInternal(&expectedMatrix);

    printf("  === Complex matrix operations passed!\n");
}

static void testErrorCases()
{
    // Test different types
    Matrix intMatrix;
    createNewMatrix(2, 2, getTypeInfoInteger(), &intMatrix);
    Matrix doubleMatrix;
    createNewMatrix(2, 2, getTypeInfoDouble(), &doubleMatrix);
    Matrix result;
    createNewMatrix(2, 2, getTypeInfoInteger(), &result);

    assert(addMatrix(&intMatrix, &doubleMatrix, &result) == ERROR_OCCURRED);

    // Test different dimensions
    Matrix m1;
    createNewMatrix(2, 3, getTypeInfoInteger(), &m1);
    Matrix m2;
    createNewMatrix(2, 2, getTypeInfoInteger(), &m2);

    assert(addMatrix(&m1, &m2, &result) == ERROR_OCCURRED);
    assert(multiplyMatrix(&m1, &m2, &result) == ERROR_OCCURRED);

    // NULL matrices
    assert(addMatrix(NULL, &m2, &result) == ERROR_OCCURRED);
    assert(addMatrix(&m1, NULL, &result) == ERROR_OCCURRED);
    assert(addMatrix(&m1, &m2, NULL) == ERROR_OCCURRED);

    removeInternal(&intMatrix);
    removeInternal(&doubleMatrix);
    removeInternal(&m1);
    removeInternal(&m2);
    removeInternal(&result);

    printf("  === Error cases passed!\n");
}

int main()
{
    printf("\n--- Starting Matrix Tests ---\n\n");

    testIntegerOperations();
    testDoubleOperations();
    testComplexOperations();
    testErrorCases();

    printf("\n--- All Tests Passed! ---\n\n");
    return 0;
}
