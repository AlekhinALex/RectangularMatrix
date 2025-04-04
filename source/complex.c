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

void substractComplex(const void *a, const void *b, void *result)
{
    const Complex *complexA = (const Complex *)a;
    const Complex *complexB = (const Complex *)b;
    Complex *complexResult = (Complex *)result;

    complexResult->real = complexA->real - complexB->real;
    complexResult->imaginary = complexA->imaginary - complexB->imaginary;
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

static void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        ;
    }
}

isSuccess readComplex(void *destination)
{
    Complex *value = (Complex *)destination;

    size_t inputSize = 0;

    double tempReal, tempImaginary;

    if (scanf(" (%lf, %lf)", &tempReal, &tempImaginary) != 2)
    {
        printf("Error: Invalid format. Try again.\n");
        clearInputBuffer();
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

void swapComplex(void *elem1, void *elem2)
{
    Complex *complex1 = (Complex *)elem1;
    Complex *complex2 = (Complex *)elem2;
    Complex temp;

    temp.real = complex1->real;
    temp.imaginary = complex1->imaginary;

    complex1->imaginary = complex2->imaginary;
    complex1->real = complex2->real;

    complex2->real = temp.real;
    complex2->imaginary = temp.imaginary;
}

void freeComplex(void *value)
{
    free(value);
}

void multiplyComplex(const void *a, const void *b, void *result)
{
    const Complex *complexA = (const Complex *)a;
    const Complex *complexB = (const Complex *)b;
    Complex *complexResult = (Complex *)result;

    complexResult->real = (complexA->real * complexB->real) - (complexA->imaginary * complexB->imaginary);
    complexResult->imaginary = (complexA->real * complexB->imaginary) + (complexA->imaginary * complexB->real);
}

static struct typeInfo *type = NULL;

const struct typeInfo *getTypeInfoComplex()
{
    if (type == NULL)
    {
        type = malloc(sizeof(struct typeInfo));
        type->size = getSizeComplex;
        type->add = addComplex;
        type->substract = substractComplex;
        type->destroy = freeComplex;
        type->multiply = multiplyComplex;
        type->print = printComplex;
        type->input = readComplex;
        type->assign = assignComplex;
        type->swap = swapComplex;
    }

    return type;
};