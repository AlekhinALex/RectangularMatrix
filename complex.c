#include <stdio.h>
#include "complex.h"

Complex ComplexSum(Complex z1, Complex z2, int sign)
{
    Complex tempComplex;
    if (sign == 1)
    {
        tempComplex.imaginary = z1.imaginary + z2.imaginary;
        tempComplex.real = z1.real + z2.real;
    }
    else
    {
        tempComplex.imaginary = z1.imaginary - z2.imaginary;
        tempComplex.real = z1.real - z2.real;
    }

    return tempComplex;
}

Complex ComplexMultiplyByComplex(Complex z1, Complex z2)
{
    Complex tempComplex;
    tempComplex.real = z1.real * z2.real - z1.imaginary * z2.imaginary;
    tempComplex.real = z1.real * z2.imaginary + z1.imaginary * z2.real;
    return tempComplex;
}