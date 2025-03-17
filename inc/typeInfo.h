#pragma once

typedef void (*binaryOperator)(const void *a, const void *b, void *result);
typedef void *(*Allocation)();
typedef void (*Print)(const void *elemenet);
typedef void (*Free)(void *element);
// typedef void (*GetSize)();
typedef void *(*Input)();

typedef struct TypeInfo
{
    binaryOperator add;
    binaryOperator substract;
    binaryOperator multiply;
    Input input;
    Allocation allocate;
    Print print;
    Free Free;
    // GetSize size; // Is it really that useful?
} TypeInfo;
