#include <stdio.h>
#include <stdlib.h>

#include "../inc/double.h"
#include "../inc/doubleImpl.h"

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

    *newDest = *newSource;
}

void swapDouble(void *elem1, void *elem2)
{
    double *dbl1 = (double *)elem1;
    double *dbl2 = (double *)elem2;

    double temp = *dbl1;

    *dbl1 = *dbl2;
    *dbl2 = temp;
}

size_t getSizeDouble()
{
    return sizeof(double);
}

isSuccess readDouble(void *destination)
{
    char *input = NULL;
    size_t inputSize = 0;
    double valueHolder;

    if (getline(&input, &inputSize, stdin) == -1)
    {
        printf("Error: Invalid input");
        free(input);
        return ERROR_OCCURRED;
    }

    char *endPtr;
    valueHolder = (double)strtod(input, &endPtr);
    if (*endPtr != '\n' && *endPtr != '\0')
    {
        printf("Error: Please enter a real number.\n");
        return ERROR_OCCURRED;
    }

    *(double *)destination = valueHolder;

    free(input);
    return SUCCESSFUL_EXECUTION;
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

static struct typeInfo *type = NULL;

const struct typeInfo *getTypeInfoDouble()
{
    if (type == NULL)
    {
        type = malloc(sizeof(struct typeInfo));
        type->assign = assignDouble;
        type->swap = swapDouble;
        type->size = getSizeDouble;
        type->add = addDouble;
        type->substract = subDouble;
        type->multiply = multiplyDouble;
        type->print = printDouble;
        type->input = readDouble;
        type->destroy = freeDouble;
    }
    return type;
};
