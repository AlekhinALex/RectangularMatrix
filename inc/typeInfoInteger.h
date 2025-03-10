#pragma once
#include "typeInfo.h"

void addInteger(const void *a, const void *b, void *result);
void subInteger(const void *a, const void *b, void *result);
void multiplyInteger(const void *a, const void *b, void *result);
void assignInteger(void *destination, const void *source);
void *allocInteger(datatype type);
void printInteger(const void *a);
void freeInteger(void *a);
