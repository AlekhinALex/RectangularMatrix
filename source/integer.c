#include <stdio.h>
#include <stdlib.h>

#include "../inc/typeInfo.h"
#include "../inc/integer.h"
#include "../inc/integerImpl.h"

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

isSuccess readInteger(void *destination)
{
    int valueHolder = 0;

    if (scanf("%d", &valueHolder) != 1)
    {
        return ERROR_OCCURRED;
    }

    *(int *)destination = valueHolder;
    destination = (void *)destination;

    return SUCCESSFUL_EXECUTION;
}

void assignInteger(void *destination, const void *source)
{
    int *newDest = (int *)destination;
    int *newSource = (int *)source;

    *newDest = *newSource;
}

size_t getSizeInteger()
{
    return sizeof(int);
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

const struct TypeInfo *getTypeInfoInteger()
{
    if (typeInfo == NULL)
    {
        typeInfo = malloc(sizeof(struct TypeInfo));
        typeInfo->size = getSizeInteger;
        typeInfo->assign = assignInteger;
        typeInfo->add = addInteger;
        typeInfo->substract = subInteger;
        typeInfo->multiply = multiplyInteger;
        typeInfo->input = readInteger;
        typeInfo->print = printInteger;
        typeInfo->Free = freeInteger;
    }
    return typeInfo;
};
