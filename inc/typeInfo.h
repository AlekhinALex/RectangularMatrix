#pragma once
#include <stdlib.h>
#include "errorHandling.h"

typedef void (*BinaryOperator)(const void *a, const void *b, void *result);
typedef size_t (*GetSize)();
typedef void (*Assignment)(void *destination, const void *source);
typedef void (*Print)(const void *element);
typedef void (*Free)(void *element);
typedef enum isSuccess (*Input)(void *destination);

typedef struct TypeInfo
{
    BinaryOperator add;
    BinaryOperator substract;
    BinaryOperator multiply;
    Assignment assign;
    Input input;
    GetSize size;
    Print print;
    Free Free;
} TypeInfo;
