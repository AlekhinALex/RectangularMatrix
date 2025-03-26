#include <stdio.h>
#include <stdlib.h>

#include "../inc/complex.h"
#include "../inc/complexImpl.h"

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
    const Complex *complex = (const Complex *)a;
    printf("[");

    printf("%g", complex->real);

    if (complex->imaginary > 0)
    {
        printf(" + %gi", complex->imaginary);
    }
    else if (complex->imaginary < 0)
    {
        printf(" - %gi", -(complex->imaginary));
    }
    else
    {
        printf(" + 0i");
    }

    printf("] ");
}

size_t getSizeComplex()
{
    return sizeof(Complex);
}

isSuccess readComplex(void *destination)
{
    Complex *value = (Complex *)destination;

    double tempReal, tempImaginary;

    if (scanf(" (%lf, %lf)", &tempReal, &tempImaginary) != 2)
    {
        return ERROR_OCCURRED;
    }

    value->real = tempReal;
    value->imaginary = tempImaginary;

    return SUCCESSFUL_EXECUTION;
}

void assignComplex(void *destination, const void *source)
{
    Complex *newDest = (Complex *)destination;
    const Complex *newSource = (Complex *)source;

    newDest->real = newSource->real;
    newDest->imaginary = newSource->imaginary;
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
        typeInfo->size = getSizeComplex;
        typeInfo->add = addComplex;
        typeInfo->Free = freeComplex;
        typeInfo->multiply = multiplyComplex;
        typeInfo->print = printComplex;
        typeInfo->input = readComplex;
    }

    return typeInfo;
};