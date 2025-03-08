#include <stdio.h>
#include <stdlib.h>

#include "../inc/typeInfo.h"
#include "../inc/double.h"
#include "../inc/typeInfoDouble.h"

static double oneGlobalConstant;
static double zeroGlobalConstant;

// const void *oneDouble()
// {
//     oneGlobalConstant.value = 1.0;
//     return &oneGlobalConstant;
// }

const void *zeroDouble()
{
    zeroGlobalConstant = 0.0;
    return &zeroGlobalConstant;
}

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

void *allocDouble(datatype type)
{
    double *newDouble = malloc(sizeof(double));
    *newDouble = 0.0;
    return newDouble;
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

static struct TypeInfo *doubleType = NULL;

const struct TypeInfo *getTypeInfoDouble()
{
    if (doubleType == NULL)
    {
        doubleType = malloc(sizeof(struct TypeInfo));
        doubleType->allocate = allocDouble;
        doubleType->assign = assignDouble;
        doubleType->add = addDouble;
        doubleType->substract = subDouble;
        doubleType->multiply = multiplyDouble;
        doubleType->print = printDouble;
        doubleType->size = sizeof(double);
        doubleType->Free = freeDouble;
        doubleType->zero = zeroDouble;
    }
    return doubleType;
};
