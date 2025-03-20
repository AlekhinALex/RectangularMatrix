#include <stdio.h>
#include <stdlib.h>

#include "../inc/typeInfo.h"
#include "../inc/double.h"
#include "../inc/typeInfoDouble.h"

void addDouble(const void *a, const void *b, void *result)
{
    double *sumDouble = (double *)result;
    const double *arg1 = (const double *)a;
    const double *arg2 = (const double *)b;

    *sumDouble = *arg1 + *arg2;
}

void subDouble(const void *a, const void *b, void *result)
{
    double *sumDouble = (double *)result;
    const double *arg1 = (const double *)a;
    const double *arg2 = (const double *)b;

    *sumDouble = *arg1 - *arg2;
}

void multiplyDouble(const void *a, const void *b, void *result)
{
    double *doubleA = (double *)a;
    double *doubleB = (double *)b;
    double *doubleResult = (double *)result;

    (*doubleResult) = (*doubleA) * (*doubleB);
}

void assignDouble(void *destination, const void *source)
{
    double *newDest = (double *)destination;
    double *newSource = (double *)source;

    newDest = newSource;
}

void *allocDouble()
{
    double *newDouble = malloc(sizeof(double));
    *newDouble = 0.0;
    return newDouble;
}

void *readDouble()
{
    double *value = malloc(sizeof(double));

    if (scanf("%lf", value) != 1)
    {
        free(value);
        return NULL;
    }

    return value;
}

void printDouble(const void *a)
{
    const double *doubl = (const double *)a;
    printf("%g ", *doubl);
}

void freeDouble(void *ptr)
{
    free(ptr);
}

static struct TypeInfo *typeInfo = NULL;

const struct TypeInfo *getTypeInfoDouble()
{
    if (typeInfo == NULL)
    {
        typeInfo = malloc(sizeof(struct TypeInfo));
        typeInfo->allocate = allocDouble;
        typeInfo->add = addDouble;
        typeInfo->substract = subDouble;
        typeInfo->multiply = multiplyDouble;
        typeInfo->print = printDouble;
        typeInfo->input = readDouble;
        typeInfo->Free = freeDouble;
    }
    return typeInfo;
};
