#include <stdlib.h>
#pragma once
typedef enum
{
    INT,
    DOUBLE,
    COMPLEX
} datatype;

typedef void (*Addition)(const void *a, const void *b, void *result);
typedef void (*Subtraction)(const void *a, const void *b, void *result);
typedef void (*Multiplication)(const void *a, const void *b, void *result);
typedef void (*Assign)(void *destination, const void *source);
typedef void *(*Allocation)(datatype type);
typedef void (*Print)(const void *elemenet);
typedef void (*Free)(void *element);
typedef void (*Size)();
typedef const void *(*Constant)();

typedef struct TypeInfo
{
    Addition add;
    Subtraction substract;
    Assign assign;
    Multiplication multiply;
    Allocation allocate;
    Print print;
    Free Free;
    size_t size;
    Constant zero;
} TypeInfo;
