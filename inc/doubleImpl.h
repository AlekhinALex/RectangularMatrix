#pragma once

#include "double.h"

#ifdef __cplusplus
extern "C"
{
#endif
    void addDouble(const void *a, const void *b, void *result);
    void subDouble(const void *a, const void *b, void *result);
    void multiplyDouble(const void *a, const void *b, void *result);
    void assignDouble(void *destination, const void *source);
    void swapDouble(void *elem1, void *elem2);
    isSuccess readDouble(void *destination);
    void printDouble(const void *a);
    void freeDouble(void *a);
#ifdef __cplusplus
}
#endif
