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

void *readInteger()
{
    int *value = malloc(sizeof(int));

    if (scanf("%d", value) != 1)
    {
        free(value);
        return NULL;
    }

    return value;
}

void *allocInteger()
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
        typeInfo->add = addInteger;
        typeInfo->substract = subInteger;
        typeInfo->multiply = multiplyInteger;
        typeInfo->input = readInteger;
        typeInfo->print = printInteger;
        typeInfo->Free = freeInteger;
    }
    return typeInfo;
};
