#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <assert.h>
#include <math.h>

#include "../inc/typeInfo.h"
#include "../inc/integer.h"
#include "../inc/double.h"
#include "../inc/complex.h"
#include "../inc/matrix.h"
#include "../inc/errorHandling.h"
#include "../inc/inputHandling.h"

void testNullMatrix()
{
    Matrix *matrix1 = NULL;
    Matrix *matrix2 = NULL;
    Matrix *result = malloc(sizeof(Matrix));

    assert(addMatrix(matrix1, matrix2, result) == ERROR_OCCURRED);
    assert(multiplyMatrix(matrix1, matrix2, result) == ERROR_OCCURRED);

    freeMatrix(result);
    printf(" - Null matrix handling tests passed\n");
}

void testComplexMatrixOperations()
{
    Matrix *matrix1 = malloc(sizeof(Matrix));
    Matrix *matrix2 = malloc(sizeof(Matrix));
    Matrix *result = malloc(sizeof(Matrix));

    matrix1->typeComponents = COMPLEX;
    matrix2->typeComponents = COMPLEX;
    matrix1->typeInfo = getTypeInfoComplex();
    matrix2->typeInfo = getTypeInfoComplex();

    matrix1->height = matrix2->height = 2;
    matrix1->length = matrix2->length = 2;

    setupMatrixElements(matrix1, 2);
    setupMatrixElements(matrix2, 2);

    for (int i = 0; i < 4; i++)
    {
        Complex *c1 = (Complex *)matrix1->data[i];
        Complex *c2 = (Complex *)matrix2->data[i];

        *(int *)c1->real = i + 1;
        *(int *)c1->imaginary = i + 2;

        *(int *)c2->real = 1;
        *(int *)c2->imaginary = 1;
    }

    result->typeComponents = COMPLEX;
    result->typeInfo = getTypeInfoComplex();
    result->height = matrix1->height;
    result->length = matrix1->length;

    assert(addMatrix(matrix1, matrix2, result) == SUCCESSFUL_EXECUTION);

    // Verify results
    for (int i = 0; i < 4; i++)
    {
        Complex *res = (Complex *)result->data[i];
        Complex *m1 = (Complex *)matrix1->data[i];
        Complex *m2 = (Complex *)matrix2->data[i];

        assert(*(int *)res->real == (*(int *)m1->real + *(int *)m2->real));
        assert(*(int *)res->imaginary == (*(int *)m1->imaginary + *(int *)m2->imaginary));
    }

    assert(multiplyMatrix(matrix1, matrix2, result) == SUCCESSFUL_EXECUTION);

    freeMatrix(matrix1);
    freeMatrix(matrix2);
    freeMatrix(result);
    printf(" - Complex matrix operations passed\n");
}

void testComplexTypeMixing()
{
    Matrix *matrix1 = malloc(sizeof(Matrix));
    Matrix *matrix2 = malloc(sizeof(Matrix));
    Matrix *result = malloc(sizeof(Matrix));

    // Setup matrices with different internal types
    matrix1->typeComponents = COMPLEX;
    matrix2->typeComponents = COMPLEX;
    matrix1->typeInfo = getTypeInfoComplex();
    matrix2->typeInfo = getTypeInfoComplex();

    matrix1->height = matrix2->height = 2;
    matrix1->length = matrix2->length = 2;

    setupMatrixElements(matrix1, 2);
    setupMatrixElements(matrix2, 1);

    // Fill matrix1 with INT complex numbers
    for (int i = 0; i < 4; i++)
    {
        Complex *c = (Complex *)matrix1->data[i];
        *(int *)c->real = i + 1;
        *(int *)c->imaginary = i + 2;
    }

    // Fill matrix2 with DOUBLE complex numbers
    for (int i = 0; i < 4; i++)
    {
        Complex *c = (Complex *)matrix2->data[i];
        *(double *)c->real = 1.5;
        *(double *)c->imaginary = 2.5;
    }

    result->typeComponents = COMPLEX;
    result->typeInfo = getTypeInfoComplex();
    result->height = matrix1->height;
    result->length = matrix1->length;

    assert(addMatrix(matrix1, matrix2, result) == ERROR_OCCURRED);

    freeMatrix(matrix1);
    freeMatrix(matrix2);
    printf(" - Complex matrix type mixing tests passed\n");
}

void testMatrixAddition()
{
    Matrix *matrix1 = malloc(sizeof(Matrix));
    Matrix *matrix2 = malloc(sizeof(Matrix));
    Matrix *result = malloc(sizeof(Matrix));

    matrix1->typeComponents = INT;
    matrix2->typeComponents = INT;
    matrix1->typeInfo = getTypeInfoInt();
    matrix2->typeInfo = getTypeInfoInt();

    matrix1->height = matrix2->height = 2;
    matrix1->length = matrix2->length = 2;

    setupMatrixElements(matrix1, 0);
    setupMatrixElements(matrix2, 0);

    // Fill matrices with test data (assuming row-major order)
    for (int i = 0; i < matrix1->height * matrix1->length; i++)
    {
        *(int *)matrix1->data[i] = i;
        *(int *)matrix2->data[i] = i;
    }

    result->typeComponents = INT;
    result->typeInfo = getTypeInfoInt();
    result->height = matrix1->height;
    result->length = matrix1->length;

    assert(addMatrix(matrix1, matrix2, result) == SUCCESSFUL_EXECUTION);

    for (int i = 0; i < matrix1->height * matrix1->length; i++)
    {
        assert(*(int *)result->data[i] == i * 2);
    }

    freeMatrix(matrix1);
    freeMatrix(matrix2);
    freeMatrix(result);
    printf(" - Matrix addition tests passed\n");
}

void testMatrixMultiplication()
{
    Matrix *matrix1 = malloc(sizeof(Matrix));
    Matrix *matrix2 = malloc(sizeof(Matrix));
    Matrix *result = malloc(sizeof(Matrix));

    matrix1->typeComponents = INT;
    matrix2->typeComponents = INT;
    matrix1->typeInfo = getTypeInfoInt();
    matrix2->typeInfo = getTypeInfoInt();

    matrix1->height = 2;
    matrix1->length = 2;
    matrix2->height = 2;
    matrix2->length = 2;

    setupMatrixElements(matrix1, 0);
    setupMatrixElements(matrix2, 0);

    // [1 2]
    // [3 4]
    *(int *)matrix1->data[0] = 1;
    *(int *)matrix1->data[1] = 2;
    *(int *)matrix1->data[2] = 3;
    *(int *)matrix1->data[3] = 4;

    // [1 0]
    // [0 1]
    *(int *)matrix2->data[0] = 1;
    *(int *)matrix2->data[1] = 0;
    *(int *)matrix2->data[2] = 0;
    *(int *)matrix2->data[3] = 1;

    assert(multiplyMatrix(matrix1, matrix2, result) == SUCCESSFUL_EXECUTION);

    assert(*(int *)result->data[0] == 1);
    assert(*(int *)result->data[1] == 2);
    assert(*(int *)result->data[2] == 3);
    assert(*(int *)result->data[3] == 4);

    freeMatrix(matrix1);
    freeMatrix(matrix2);
    freeMatrix(result);
    printf(" - Matrix multiplication tests passed\n");
}

void testIncompatibleMatrices()
{
    Matrix *matrix1 = malloc(sizeof(Matrix));
    Matrix *matrix2 = malloc(sizeof(Matrix));
    Matrix *result = malloc(sizeof(Matrix));

    matrix1->typeComponents = INT;
    matrix2->typeComponents = INT;
    matrix1->typeInfo = getTypeInfoInt();
    matrix2->typeInfo = getTypeInfoInt();

    // set different sizes
    matrix1->height = 2;
    matrix1->length = 3;
    matrix2->height = 2;
    matrix2->length = 2;

    setupMatrixElements(matrix1, 0);
    setupMatrixElements(matrix2, 0);

    assert(addMatrix(matrix1, matrix2, result) == ERROR_OCCURRED);
    assert(multiplyMatrix(matrix1, matrix2, result) == ERROR_OCCURRED);

    freeMatrix(matrix1);
    freeMatrix(matrix2);
    freeMatrix(result);
    printf(" - Incompatible matrices tests passed\n");
}

void testLargeComplexMatrix()
{
    int SIZE = 1000; //* 1000x1000 matrix
    Matrix *matrix1 = malloc(sizeof(Matrix));
    Matrix *matrix2 = malloc(sizeof(Matrix));
    Matrix *result = malloc(sizeof(Matrix));

    matrix1->typeComponents = COMPLEX;
    matrix2->typeComponents = COMPLEX;
    matrix1->typeInfo = getTypeInfoComplex();
    matrix2->typeInfo = getTypeInfoComplex();

    matrix1->height = matrix2->height = SIZE;
    matrix1->length = matrix2->length = SIZE;

    setupMatrixElements(matrix1, 1);
    setupMatrixElements(matrix2, 1);

    // filing matricies
    for (int i = 0; i < SIZE * SIZE; i++)
    {
        Complex *c1 = (Complex *)matrix1->data[i];
        Complex *c2 = (Complex *)matrix2->data[i];

        *(double *)c1->real = i * 0.5;
        *(double *)c1->imaginary = i * 0.3;

        *(double *)c2->real = 3.2;
        *(double *)c2->imaginary = 1.0;
    }

    result->typeComponents = COMPLEX;
    result->typeInfo = getTypeInfoComplex();
    result->height = SIZE;
    result->length = SIZE;
    setupMatrixElements(result, 1);

    assert(addMatrix(matrix1, matrix2, result) == SUCCESSFUL_EXECUTION);

    for (int i = 0; i < SIZE * SIZE; i++)
    {
        Complex *r = (Complex *)result->data[i];
        double expected_real = i * 0.5 + 3.2;
        double expected_imag = i * 0.3 + 1.0;

        double epsilon = 1e-10;
        assert(fabs(*(double *)r->real - expected_real) < epsilon);
        assert(fabs(*(double *)r->imaginary - expected_imag) < epsilon);
    }

    assert(multiplyMatrix(matrix1, matrix2, result) == SUCCESSFUL_EXECUTION);

    freeMatrix(matrix1);
    freeMatrix(matrix2);
    freeMatrix(result);
    printf(" - Large complex matrix operations passed\n");
}

void testMixedTypeOperations()
{
    Matrix *intMatrix = malloc(sizeof(Matrix));
    Matrix *doubleMatrix = malloc(sizeof(Matrix));
    Matrix *complexMatrix = malloc(sizeof(Matrix));
    Matrix *result = malloc(sizeof(Matrix));

    int SIZE = 3;

    // INT matrix
    intMatrix->typeComponents = INT;
    intMatrix->typeInfo = getTypeInfoInt();
    intMatrix->height = intMatrix->length = SIZE;
    setupMatrixElements(intMatrix, 0);

    // DOUBLE matrix
    doubleMatrix->typeComponents = DOUBLE;
    doubleMatrix->typeInfo = getTypeInfoDouble();
    doubleMatrix->height = doubleMatrix->length = SIZE;
    setupMatrixElements(doubleMatrix, 0);

    // COMPLEX matrix
    complexMatrix->typeComponents = COMPLEX;
    complexMatrix->typeInfo = getTypeInfoComplex();
    complexMatrix->height = complexMatrix->length = SIZE;
    setupMatrixElements(complexMatrix, 2);

    for (int i = 0; i < SIZE * SIZE; i++)
    {
        *(int *)intMatrix->data[i] = i + 1;

        *(double *)doubleMatrix->data[i] = (i + 1) * 0.5;

        Complex *c = (Complex *)complexMatrix->data[i];
        c->real = malloc(sizeof(int));
        c->imaginary = malloc(sizeof(int));
        *(int *)c->real = i;
        *(int *)c->imaginary = i + 1;
    }

    result->height = SIZE;
    result->length = SIZE;

    // INT + DOUBLE (should fail)
    result->typeComponents = DOUBLE;
    result->typeInfo = getTypeInfoDouble();
    setupMatrixElements(result, 0);
    assert(addMatrix(intMatrix, doubleMatrix, result) == ERROR_OCCURRED);

    // INT + COMPLEX (should fail)
    result->typeComponents = COMPLEX;
    result->typeInfo = getTypeInfoComplex();
    setupMatrixElements(result, 2);
    assert(addMatrix(intMatrix, complexMatrix, result) == ERROR_OCCURRED);

    freeMatrix(intMatrix);
    freeMatrix(doubleMatrix);
    freeMatrix(complexMatrix);
    freeMatrix(result);

    printf(" - Mixed type operations tests passed\n");
}

int main()
{
    system("clear");

    printf("\n===Starting matrix tests===\n\n");

    testNullMatrix();
    testMatrixAddition();
    testMatrixMultiplication();
    testIncompatibleMatrices();
    testComplexMatrixOperations();
    testComplexTypeMixing();
    testLargeComplexMatrix();
    testMixedTypeOperations();

    printf("\n===RESULT: All tests passed====\n\n");
    return 0;
}
