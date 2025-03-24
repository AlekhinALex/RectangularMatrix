#pragma once

#include "double.h"

void addDouble(const void *a, const void *b, void *result);
void subDouble(const void *a, const void *b, void *result);
void multiplyDouble(const void *a, const void *b, void *result);
void assignDouble(void *destination, const void *source);
void *allocDouble();
isSuccess readDouble(void *destination);
void printDouble(const void *a);
void freeDouble(void *a);