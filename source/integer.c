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
    char *input = NULL;
    size_t inputSize = 0;
    int valueHolder;

    if (getline(&input, &inputSize, stdin) == -1)
    {
        printf("Error: Invalid input");
        free(input);
        return ERROR_OCCURRED;
    }

    char *endPtr;
    valueHolder = (int)strtol(input, &endPtr, 10);
    if (*endPtr != '\n' && *endPtr != '\0')
    {
        printf("Error: Please enter an integer number.\n");
        return ERROR_OCCURRED;
    }

    *(int *)destination = valueHolder;

    free(input);
    return SUCCESSFUL_EXECUTION;
}

void assignInteger(void *destination, const void *source)
{
    int *newDest = (int *)destination;
    int *newSource = (int *)source;

    *newDest = *newSource;
}

void swapInteger(void *elem1, void *elem2)
{
    int *dbl1 = (int *)elem1;
    int *dbl2 = (int *)elem2;

    int temp = *dbl1;

    *dbl1 = *dbl2;
    *dbl2 = temp;
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

static struct typeInfo *type = NULL;

const struct typeInfo *getTypeInfoInteger()
{
    if (type == NULL)
    {
        type = malloc(sizeof(struct typeInfo));
        type->size = getSizeInteger;
        type->assign = assignInteger;
        type->swap = swapInteger;
        type->add = addInteger;
        type->substract = subInteger;
        type->multiply = multiplyInteger;
        type->input = readInteger;
        type->print = printInteger;
        type->destroy = freeInteger;
    }
    return type;
};
