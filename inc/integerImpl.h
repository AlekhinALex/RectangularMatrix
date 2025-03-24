#pragma once

#include "integer.h"

void addInteger(const void *a, const void *b, void *result);
void subInteger(const void *a, const void *b, void *result);
void multiplyInteger(const void *a, const void *b, void *result);
void assignInteger(void *destination, const void *source);
void *allocInteger();
isSuccess readInteger(void *destination);
void printInteger(const void *a);
void freeInteger(void *a);
