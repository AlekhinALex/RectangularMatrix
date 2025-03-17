#pragma once
#include "typeInfo.h"

typedef struct Complex
{
    double real;
    double imaginary;
} Complex;

void addComplex(const void *a, const void *b, void *result);
void multiplyComplex(const void *, const void *, void *result);
void printComplex(const void *complex);
void *allocComplex();
void *readComplex();
void freeComplex(void *value);
void assignComplex(void *dest, const void *src);
