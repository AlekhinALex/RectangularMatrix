#pragma once

#include "integer.h"
#include "double.h"
#include "complex.h"
#include "matrix.h"

typedef void (*BinaryOperator)(const void *a, const void *b, void *result);
typedef void *(*Allocation)();
typedef void (*Print)(const void *elemenet);
typedef void (*Free)(void *element);
typedef void *(*Input)();

typedef struct TypeInfo
{
    BinaryOperator add;
    BinaryOperator substract;
    BinaryOperator multiply;
    Input input;
    Allocation allocate;
    Print print;
    Free Free;
} TypeInfo;
