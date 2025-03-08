#pragma once
#include "typeInfo.h"

void addInteger(const void *a, const void *b, void *result);
void subInteger(const void *a, const void *b, void *result);
void multiplyInteger(const void *a, const void *b, void *result);
// void additionForInteger(const void *a, const void *b, void *result, BinaryOperator functionName);
// void substractionForInteger(const void *a, const void *b, void *result, BinaryOperator functionName);
// void multiplicationForInteger(const void *a, const void *b, void *result, BinaryOperator functionName);
void assignInteger(void *destination, const void *source); //? Is it needed?
const void *oneInteger();
const void *zeroInteger();
// TODO: MAY BE DeLeTe -> const void *getType();
void *allocInteger(datatype type);
void printInteger(const void *a);
void freeInteger(void *a);
