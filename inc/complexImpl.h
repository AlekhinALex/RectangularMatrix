#pragma once

#include "complex.h"

typedef struct Complex
{
    double real;
    double imaginary;
} Complex;

void addComplex(const void *a, const void *b, void *result);
void multiplyComplex(const void *, const void *, void *result);
void printComplex(const void *complex);
void *allocComplex();
isSuccess readComplex(void *destination);
void freeComplex(void *value);
