#pragma once

#include "integer.h"

#ifdef __cplusplus
extern "C"
{
#endif
    void addInteger(const void *a, const void *b, void *result);
    void subInteger(const void *a, const void *b, void *result);
    void multiplyInteger(const void *a, const void *b, void *result);
    void assignInteger(void *destination, const void *source);
    void swapInteger(void *element1, void *element2);
    isSuccess readInteger(void *destination);
    void printInteger(const void *a);
    void freeInteger(void *a);
#ifdef __cplusplus
}
#endif
