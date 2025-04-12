#include <gtest/gtest.h>
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

TEST(MatrixTests, MatrixIntegerAddition)
{
    Matrix m1, m2, result, expectedResult;
    createNewMatrix(2, 2, getTypeInfoInteger(), &m1);
    createNewMatrix(2, 2, getTypeInfoInteger(), &m2);
    createNewMatrix(2, 2, getTypeInfoInteger(), &result);
    createNewMatrix(2, 2, getTypeInfoInteger(), &expectedResult);

    int values1[] = {1, 2, 3, 4};
    int values2[] = {5, 6, 7, 8};
    int expected[] = {6, 8, 10, 12};

    memcpy(m1.data, values1, sizeof(values1));
    memcpy(m2.data, values2, sizeof(values2));
    memcpy(expectedResult.data, expected, sizeof(expected));

    EXPECT_EQ(addMatrix(&m1, &m2, &result), SUCCESSFUL_EXECUTION);
    EXPECT_EQ(memcmp(result.data, expectedResult.data, sizeof(expected)), 0);

    removeInternal(&m1);
    removeInternal(&m2);
    removeInternal(&result);
    removeInternal(&expectedResult);
}

TEST(MatrixTests, MatrixDoubleAddition)
{
    Matrix m1, m2, result, expectedResult;
    createNewMatrix(2, 2, getTypeInfoDouble(), &m1);
    createNewMatrix(2, 2, getTypeInfoDouble(), &m2);
    createNewMatrix(2, 2, getTypeInfoDouble(), &result);
    createNewMatrix(2, 2, getTypeInfoDouble(), &expectedResult);

    double values1[] = {1.5, 2.5, 3.5, 4.5};
    double values2[] = {0.5, 1.5, 2.5, 3.5};
    double expected[] = {2.0, 4.0, 6.0, 8.0};

    memcpy(m1.data, values1, sizeof(values1));
    memcpy(m2.data, values2, sizeof(values2));
    memcpy(expectedResult.data, expected, sizeof(expected));

    EXPECT_EQ(addMatrix(&m1, &m2, &result), SUCCESSFUL_EXECUTION);
    EXPECT_EQ(memcmp(result.data, expectedResult.data, sizeof(expected)), 0);

    removeInternal(&m1);
    removeInternal(&m2);
    removeInternal(&result);
    removeInternal(&expectedResult);
}

TEST(MatrixTests, MatrixComplexAddition)
{
    Matrix m1, m2, result, expectedResult;
    createNewMatrix(2, 2, getTypeInfoComplex(), &m1);
    createNewMatrix(2, 2, getTypeInfoComplex(), &m2);
    createNewMatrix(2, 2, getTypeInfoComplex(), &result);
    createNewMatrix(2, 2, getTypeInfoComplex(), &expectedResult);

    Complex values1[] = {{1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}, {4.0, 4.0}};
    Complex values2[] = {{0.5, 0.5}, {1.5, 1.5}, {2.5, 2.5}, {3.5, 3.5}};
    Complex expected[] = {{1.5, 1.5}, {3.5, 3.5}, {5.5, 5.5}, {7.5, 7.5}};

    memcpy(m1.data, values1, sizeof(values1));
    memcpy(m2.data, values2, sizeof(values2));
    memcpy(expectedResult.data, expected, sizeof(expected));

    EXPECT_EQ(addMatrix(&m1, &m2, &result), SUCCESSFUL_EXECUTION);
    EXPECT_EQ(memcmp(result.data, expectedResult.data, sizeof(expected)), 0);

    removeInternal(&m1);
    removeInternal(&m2);
    removeInternal(&result);
    removeInternal(&expectedResult);
}

TEST(MatrixTests, MatrixIntegerMultiplication)
{
    Matrix m1, m2, result, expectedResult;
    createNewMatrix(4, 4, getTypeInfoInteger(), &m1);
    createNewMatrix(4, 4, getTypeInfoInteger(), &m2);
    createNewMatrix(4, 4, getTypeInfoInteger(), &result);
    createNewMatrix(4, 4, getTypeInfoInteger(), &expectedResult);

    int values1[] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16};

    int values2[] = {
        16, 15, 14, 13,
        12, 11, 10, 9,
        8, 7, 6, 5,
        4, 3, 2, 1};

    int expected[] = {
        80, 70, 60, 50,
        240, 214, 188, 162,
        400, 358, 316, 274,
        560, 502, 444, 386};

    memcpy(m1.data, values1, sizeof(values1));
    memcpy(m2.data, values2, sizeof(values2));
    memcpy(expectedResult.data, expected, sizeof(expected));

    EXPECT_EQ(multiplyMatrix(&m1, &m2, &result), SUCCESSFUL_EXECUTION);
    EXPECT_EQ(memcmp(result.data, expectedResult.data, sizeof(expected)), 0);

    removeInternal(&m1);
    removeInternal(&m2);
    removeInternal(&result);
    removeInternal(&expectedResult);
}

TEST(MatrixTests, MatrixDoubleMultiplication)
{
    Matrix m1, m2, result, expectedResult;
    createNewMatrix(4, 4, getTypeInfoDouble(), &m1);
    createNewMatrix(4, 4, getTypeInfoDouble(), &m2);
    createNewMatrix(4, 4, getTypeInfoDouble(), &result);
    createNewMatrix(4, 4, getTypeInfoDouble(), &expectedResult);

    double values1[] = {
        1.5, 2.5, 3.5, 4.5,
        5.5, 6.5, 7.5, 8.5,
        9.5, 10.5, 11.5, 12.5,
        13.5, 14.5, 15.5, 16.5};

    double values2[] = {
        16.5, 15.5, 14.5, 13.5,
        12.5, 11.5, 10.5, 9.5,
        8.5, 7.5, 6.5, 5.5,
        4.5, 3.5, 2.5, 1.5};

    double expected[] = {
        106.0, 94.0, 82.0, 70.0,
        274.0, 246.0, 218.0, 190.0,
        442.0, 398.0, 354.0, 310.0,
        610.0, 550.0, 490.0, 430.0};

    memcpy(m1.data, values1, sizeof(values1));
    memcpy(m2.data, values2, sizeof(values2));
    memcpy(expectedResult.data, expected, sizeof(expected));

    EXPECT_EQ(multiplyMatrix(&m1, &m2, &result), SUCCESSFUL_EXECUTION);
    EXPECT_EQ(memcmp(result.data, expectedResult.data, sizeof(expected)), 0);

    removeInternal(&m1);
    removeInternal(&m2);
    removeInternal(&result);
    removeInternal(&expectedResult);
}

TEST(MatrixTests, MatrixComplexMultiplication)
{
    Matrix m1, m2, result, expectedResult;
    createNewMatrix(4, 4, getTypeInfoComplex(), &m1);
    createNewMatrix(4, 4, getTypeInfoComplex(), &m2);
    createNewMatrix(4, 4, getTypeInfoComplex(), &result);
    createNewMatrix(4, 4, getTypeInfoComplex(), &expectedResult);

    Complex values1[] = {{1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}, {4.0, 4.0}, {5.0, 5.0}, {6.0, 6.0}, {7.0, 7.0}, {8.0, 8.0}, {9.0, 9.0}, {10.0, 10.0}, {11.0, 11.0}, {12.0, 12.0}, {13.0, 13.0}, {14.0, 14.0}, {15.0, 15.0}, {16.0, 16.0}};

    Complex values2[] = {{16.0, 16.0}, {15.0, 15.0}, {14.0, 14.0}, {13.0, 13.0}, {12.0, 12.0}, {11.0, 11.0}, {10.0, 10.0}, {9.0, 9.0}, {8.0, 8.0}, {7.0, 7.0}, {6.0, 6.0}, {5.0, 5.0}, {4.0, 4.0}, {3.0, 3.0}, {2.0, 2.0}, {1.0, 1.0}};

    Complex expected[] = {{0.0, 160.0}, {0.0, 140.0}, {0.0, 120.0}, {0.0, 100.0}, {0.0, 480.0}, {0.0, 428.0}, {0.0, 376.0}, {0.0, 324.0}, {0.0, 800.0}, {0.0, 716.0}, {0.0, 632.0}, {0.0, 548.0}, {0.0, 1120.0}, {0.0, 1004.0}, {0.0, 888.0}, {0.0, 772.0}};

    memcpy(m1.data, values1, sizeof(values1));
    memcpy(m2.data, values2, sizeof(values2));
    memcpy(expectedResult.data, expected, sizeof(expected));

    EXPECT_EQ(multiplyMatrix(&m1, &m2, &result), SUCCESSFUL_EXECUTION);
    EXPECT_EQ(memcmp(result.data, expectedResult.data, sizeof(expected)), 0);

    removeInternal(&m1);
    removeInternal(&m2);
    removeInternal(&result);
    removeInternal(&expectedResult);
}

TEST(MatrixTests, ErrorCases)
{
    Matrix intMatrix, doubleMatrix, result, diffDimM1, diffDimM2;
    createNewMatrix(2, 2, getTypeInfoInteger(), &intMatrix);
    createNewMatrix(2, 2, getTypeInfoDouble(), &doubleMatrix);
    createNewMatrix(2, 2, getTypeInfoInteger(), &result);
    createNewMatrix(2, 3, getTypeInfoInteger(), &diffDimM1);
    createNewMatrix(2, 2, getTypeInfoInteger(), &diffDimM2);

    EXPECT_EQ(addMatrix(&intMatrix, &doubleMatrix, &result), ERROR_OCCURRED);

    EXPECT_EQ(addMatrix(NULL, &intMatrix, &result), ERROR_OCCURRED);
    EXPECT_EQ(addMatrix(&doubleMatrix, NULL, &result), ERROR_OCCURRED);
    EXPECT_EQ(addMatrix(&intMatrix, &doubleMatrix, NULL), ERROR_OCCURRED);

    EXPECT_EQ(addMatrix(&diffDimM1, &diffDimM2, &result), ERROR_OCCURRED);
    EXPECT_EQ(multiplyMatrix(&diffDimM1, &diffDimM2, &result), ERROR_OCCURRED);

    removeInternal(&intMatrix);
    removeInternal(&doubleMatrix);
    removeInternal(&diffDimM1);
    removeInternal(&diffDimM2);
    removeInternal(&result);
}

TEST(TypeTests, IntegerOperations)
{
    int a = 5;
    int b = 3;
    int result = 0;

    getTypeInfoInteger()->add(&a, &b, &result);
    EXPECT_EQ(result, 8);

    getTypeInfoInteger()->substract(&a, &b, &result);
    EXPECT_EQ(result, 2);

    getTypeInfoInteger()->multiply(&a, &b, &result);
    EXPECT_EQ(result, 15);
}

TEST(TypeTests, DoubleOperations)
{
    double a = 5.5;
    double b = 2.5;
    double result = 0;

    getTypeInfoDouble()->add(&a, &b, &result);
    EXPECT_DOUBLE_EQ(result, 8.0);

    getTypeInfoDouble()->substract(&a, &b, &result);
    EXPECT_DOUBLE_EQ(result, 3.0);

    getTypeInfoDouble()->multiply(&a, &b, &result);
    EXPECT_DOUBLE_EQ(result, 13.75);
}

TEST(TypeTests, ComplexOperations)
{
    Complex a = {3.0, 2.0};
    Complex b = {1.0, 4.0};
    Complex result = {0};

    const typeInfo *complexType = getTypeInfoComplex();

    complexType->add(&a, &b, &result);
    EXPECT_DOUBLE_EQ(result.real, 4.0);
    EXPECT_DOUBLE_EQ(result.imaginary, 6.0);

    complexType->substract(&a, &b, &result);
    EXPECT_DOUBLE_EQ(result.real, 2.0);
    EXPECT_DOUBLE_EQ(result.imaginary, -2.0);

    complexType->multiply(&a, &b, &result);
    EXPECT_DOUBLE_EQ(result.real, -5.0);
    EXPECT_DOUBLE_EQ(result.imaginary, 14.0);
}

TEST(AdditionalTest, newFuncionTests)
{
    Matrix matrixDouble, matrixComplex;
    createNewMatrix(4, 4, getTypeInfoDouble(), &matrixDouble);
    createNewMatrix(4, 4, getTypeInfoComplex(), &matrixComplex);

    double values1[] = {
        1.5, 2.5, 3.5, 4.5,
        5.5, 6.5, 7.5, 8.5,
        9.5, 10.5, 11.5, 12.5,
        13.5, 14.5, 15.5, 16.5};

    Complex values2[] = {{-777, 123}, {1.5, 1.5}, {2.5, 2.5}, {3.5, 3.5}, {0.5, 0.5}, {1.5, 1.5}, {0.999, 0.999}, {3.5, 3.5}, {0.5, 0.5}, {1.5, 1.5}, {2.5, 2.5}, {3.5, 3.5}, {0.5, 0.5}, {1.5, 1.5}, {2.5, 2.5}, {192, -2025.2025}};

    memcpy(matrixDouble.data, values1, sizeof(values1));
    memcpy(matrixComplex.data, values2, sizeof(values2));

    EXPECT_DOUBLE_EQ(printMatrixElement(&matrixDouble, 1, 1), SUCCESSFUL_EXECUTION);
    EXPECT_DOUBLE_EQ(printMatrixElement(&matrixDouble, 4, 4), SUCCESSFUL_EXECUTION);
    EXPECT_DOUBLE_EQ(printMatrixElement(&matrixDouble, 2, 3), SUCCESSFUL_EXECUTION);
    std::cout << "\n";
    EXPECT_DOUBLE_EQ(printMatrixElement(&matrixComplex, 1, 1), SUCCESSFUL_EXECUTION);
    EXPECT_DOUBLE_EQ(printMatrixElement(&matrixComplex, 4, 4), SUCCESSFUL_EXECUTION);
    EXPECT_DOUBLE_EQ(printMatrixElement(&matrixComplex, 2, 3), SUCCESSFUL_EXECUTION);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}