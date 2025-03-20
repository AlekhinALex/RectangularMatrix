#include <stdio.h>
#include <stdlib.h>

#include "../inc/complex.h"
#include "../inc/typeInfoComplex.h"

void addComplex(const void *a, const void *b, void *result)
{

    const Complex *complexA = (const Complex *)a;
    const Complex *complexB = (const Complex *)b;
    Complex *complexResult = (Complex *)result;

    complexResult->real = complexA->real + complexB->real;
    complexResult->imaginary = complexA->imaginary + complexB->imaginary;
}

void printComplex(const void *a)
{
    if (!a)
    {
        printf("NULL ptr detected\n");
        return;
    }
    const Complex *complex = (const Complex *)a;
    if (!complex->real || !complex->imaginary)
    {
        printf("Invalid complex number pointers\n");
        return;
    }
    printf("[");

    printf("%g", complex->real);

    if (complex->imaginary > 0)
        printf(" + %gi", complex->imaginary);
    else if (complex->imaginary < 0)
        printf(" - %gi", -(complex->imaginary));
    else
        printf(" + 0i");

    printf("] ");
}

void *allocComplex()
{
    Complex *complex = malloc(sizeof(Complex));
    if (complex == NULL)
    {
        printf("Memory allocation failed for complex number\n");
        return NULL;
    }

    complex->real = 0.0;
    complex->imaginary = 0.0;

    return complex;
}

void *readComplex()
{
    Complex *value = malloc(sizeof(Complex));

    double tempReal, tempImaginary;

    if (scanf(" (%lf, %lf)", &tempReal, &tempImaginary) != 2)
    {
        free(value);
        return NULL;
    }

    value->real = tempReal;
    value->imaginary = tempImaginary;

    return value;
}

void freeComplex(void *value)
{
    Complex *complex = (Complex *)value;
    free(complex);
}

void multiplyComplex(const void *a, const void *b, void *result)
{
    const Complex *complexA = (const Complex *)a;
    const Complex *complexB = (const Complex *)b;
    Complex *complexResult = (Complex *)result;

    complexResult->real = (complexA->real * complexB->real) - (complexA->imaginary * complexB->imaginary);
    complexResult->imaginary = (complexA->real * complexB->imaginary) + (complexA->imaginary * complexB->real);
}

static struct TypeInfo *typeInfo = NULL;

const struct TypeInfo *getTypeInfoComplex()
{
    if (typeInfo == NULL)
    {
        typeInfo = malloc(sizeof(struct TypeInfo));
        typeInfo->allocate = allocComplex;
        typeInfo->add = addComplex;
        typeInfo->Free = freeComplex;
        typeInfo->multiply = multiplyComplex;
        typeInfo->print = printComplex;
    }

    return typeInfo;
};