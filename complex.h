#pragma once
typedef struct Complex
{
  double imaginary;
  double real;
} Complex;

Complex ComplexSum(Complex a, Complex b, int sign); // if sign = 1 : a + b, else = a - b
Complex ComplexMultiplyByConstant(double constant, Complex a);
Complex ComplexMultiplyByComplex(Complex a, Complex b);
