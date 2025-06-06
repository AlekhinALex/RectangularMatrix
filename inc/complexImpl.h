#pragma once

#include "complex.h"
#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct Complex
    {
        double real;
        double imaginary;
    } Complex;

    void addComplex(const void *a, const void *b, void *result);
    void substractComplex(const void *a, const void *b, void *result);
    void multiplyComplex(const void *, const void *, void *result);
    void assignComplex(void *destination, const void *source);
    void swapComplex(void *elem1, void *elem2);
    void printComplex(const void *complex);
    isSuccess readComplex(void *destination);
    void freeComplex(void *value);

#ifdef __cplusplus
}
#endif
