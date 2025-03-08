#include <stdio.h>
#include <stdlib.h>

#include "../inc/complex.h"
#include "../inc/typeInfoComplex.h"

void addComplex(const void *a, const void *b, void *result)
{

    const Complex *complexA = (const Complex *)a;
    const Complex *complexB = (const Complex *)b;
    Complex *complexResult = (Complex *)result;

    if (complexA->type == INT)
    {
        int *resultReal = (int *)complexResult->real;
        int *resultImag = (int *)complexResult->imaginary;

        *resultReal = *(int *)complexA->real + *(int *)complexB->real;
        *resultImag = *(int *)complexA->imaginary + *(int *)complexB->imaginary;
    }
    else if (complexA->type == DOUBLE)
    {
        double *resultReal = (double *)complexResult->real;
        double *resultImag = (double *)complexResult->imaginary;

        *resultReal = *(double *)complexA->real + *(double *)complexB->real;
        *resultImag = *(double *)complexA->imaginary + *(double *)complexB->imaginary;
    }
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

    if (complex->type == INT)
    {
        int real = *(int *)complex->real;
        int imag = *(int *)complex->imaginary;

        printf("%d", real);

        if (imag > 0)
            printf(" + %di", imag);
        else if (imag < 0)
            printf(" - %di", -imag);
        else
            printf(" + 0i");
    }
    else if (complex->type == DOUBLE)
    {
        double real = *(double *)complex->real;
        double imag = *(double *)complex->imaginary;

        printf("%g", real);

        if (imag > 0)
            printf(" + %gi", imag);
        else if (imag < 0)
            printf(" - %gi", -imag);
        else
            printf(" + 0i");
    }

    printf("] ");
}

void assignComplex(void *dest, const void *src)
{
    Complex *destComplex = (Complex *)dest;
    const Complex *srcComplex = (const Complex *)src;

    destComplex->type = srcComplex->type;

    if (srcComplex->type == INT)
    {
        *(int *)destComplex->real = *(int *)srcComplex->real;
        *(int *)destComplex->imaginary = *(int *)srcComplex->imaginary;
    }
    else if (srcComplex->type == DOUBLE)
    {
        *(double *)destComplex->real = *(double *)srcComplex->real;
        *(double *)destComplex->imaginary = *(double *)srcComplex->imaginary;
    }
}

void *allocComplex(datatype type)
{
    if (type != INT && type != DOUBLE)
    {
        printf("Unknown type to allocate\n");
        return NULL;
    }

    Complex *complex = malloc(sizeof(Complex));
    if (complex == NULL)
    {
        printf("Memory allocation failed for complex number\n");
        return NULL;
    }

    complex->type = type;

    if (type == INT)
    {
        complex->real = malloc(sizeof(int));
        complex->imaginary = malloc(sizeof(int));

        if (complex->real == NULL || complex->imaginary == NULL)
        {
            printf("Memory allocation failed for complex number components\n");
            freeComplex(complex);
            return NULL;
        }

        *(int *)complex->real = 0;
        *(int *)complex->imaginary = 0;
    }
    else if (type == DOUBLE)
    {
        complex->real = malloc(sizeof(double));
        complex->imaginary = malloc(sizeof(double));

        if (complex->real == NULL || complex->imaginary == NULL)
        {
            printf("Memory allocation failed for complex number components\n");
            freeComplex(complex);
            return NULL;
        }

        *(double *)complex->real = 0.0;
        *(double *)complex->imaginary = 0.0;
    }

    return complex;
}

void freeComplex(void *value)
{
    Complex *complex = (Complex *)value;
    free(complex->imaginary);
    free(complex->real);
    free(complex);
}

void multiplyComplex(const void *a, const void *b, void *result)
{
    const Complex *complexA = (const Complex *)a;
    const Complex *complexB = (const Complex *)b;
    Complex *complexResult = (Complex *)result;

    // complex multiplication: (a + bi) * (c + di) = (ac - bd) + (ad + bc)i

    if (complexA->type == INT)
    {
        int realA = *(int *)complexA->real;
        int imagA = *(int *)complexA->imaginary;
        int realB = *(int *)complexB->real;
        int imagB = *(int *)complexB->imaginary;

        // real part: ac - bd
        *(int *)complexResult->real = (realA * realB) - (imagA * imagB);

        // imaginary part: ad + bc
        *(int *)complexResult->imaginary = (realA * imagB) + (imagA * realB);
    }
    else if (complexA->type == DOUBLE)
    {
        double realA = *(double *)complexA->real;
        double imagA = *(double *)complexA->imaginary;
        double realB = *(double *)complexB->real;
        double imagB = *(double *)complexB->imaginary;

        // real part: ac - bd
        *(double *)complexResult->real = (realA * realB) - (imagA * imagB);

        // imaginary part: ad + bc
        *(double *)complexResult->imaginary = (realA * imagB) + (imagA * realB);
    }
}

static struct TypeInfo *typeInfo = NULL;

const struct TypeInfo *getTypeInfoComplex()
{
    if (typeInfo == NULL)
    {
        typeInfo = malloc(sizeof(struct TypeInfo));
        if (typeInfo == NULL)
        {
            printf("Memory alloction failed.");
            exit(1);
        }
        typeInfo->allocate = allocComplex;
        typeInfo->assign = assignComplex;
        typeInfo->size = sizeof(Complex);
        typeInfo->add = addComplex;
        typeInfo->Free = freeComplex;
        typeInfo->multiply = multiplyComplex;
        typeInfo->print = printComplex;
    }

    return typeInfo;
};