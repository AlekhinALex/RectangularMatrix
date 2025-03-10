#include <stdio.h>
#include <stdlib.h>

#include "../inc/typeInfo.h"
#include "../inc/integer.h"
#include "../inc/typeInfoInteger.h"

void addInteger(const void *a, const void *b, void *result)
{
    int *sumInt = (int *)result;

    const int *arg1 = (const int *)a;
    const int *arg2 = (const int *)b;

    *sumInt = *arg1 + *arg2;
}

void subInteger(const void *a, const void *b, void *result)
{
    int *sumInt = (int *)result;

    const int *arg1 = (const int *)a;
    const int *arg2 = (const int *)b;

    *sumInt = *arg1 - *arg2;
}

void multiplyInteger(const void *a, const void *b, void *result)
{
    int *intA = (int *)a;
    int *intB = (int *)b;
    int *intResult = (int *)result;

    (*intResult) = (*intA) * (*intB);
}

//? Is really needed?
void assignInteger(void *destination, const void *source)
{
    int *newDest = (int *)destination;
    int *newSource = (int *)source;

    newDest = newSource;
}

void *allocInteger(datatype type)
{
    int *newInt = malloc(sizeof(int));
    *newInt = 0;
    return newInt;
}

void printInteger(const void *a)
{
    const int *integer = (const int *)a;
    printf("%d ", *integer);
}

void freeInteger(void *ptr)
{
    free(ptr);
}

static struct TypeInfo *typeInfo = NULL;

const struct TypeInfo *getTypeInfoInt()
{
    if (typeInfo == NULL)
    {
        typeInfo = malloc(sizeof(struct TypeInfo));
        typeInfo->allocate = allocInteger;
        typeInfo->assign = assignInteger;
        typeInfo->add = addInteger;
        typeInfo->substract = subInteger;
        typeInfo->multiply = multiplyInteger;
        typeInfo->size = sizeof(int);
        typeInfo->print = printInteger;
        typeInfo->Free = freeInteger;
    }
    return typeInfo;
};
