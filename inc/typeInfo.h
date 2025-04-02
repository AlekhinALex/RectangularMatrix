#pragma once
#include <stdlib.h>
typedef enum isSuccess
{
    ERROR_OCCURRED,
    SUCCESSFUL_EXECUTION
} isSuccess;

typedef void (*binaryOperator)(const void *a, const void *b, void *result);
typedef size_t (*getSize)();

//? Do I need both assign and swap?
typedef void (*assignment)(void *destination, const void *source);
typedef void (*changePlaces)(void *element1, void *element2);

typedef void (*print)(const void *element);
typedef void (*destroy)(void *element);
typedef enum isSuccess (*input)(void *destination);

typedef struct typeInfo
{
    binaryOperator add;
    binaryOperator substract;
    binaryOperator multiply;
    assignment assign;
    changePlaces swap;
    input input;
    getSize size;
    print print;
    destroy destroy;
} typeInfo;
