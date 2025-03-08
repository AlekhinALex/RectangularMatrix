#pragma once

void addDouble(const void *a, const void *b, void *result);
void subDouble(const void *a, const void *b, void *result);
void multiplyDouble(const void *a, const void *b, void *result);
void assignDouble(void *destination, const void *source);
// const void *oneDouble();
const void *zeroDouble();
// const void *getType();
void *allocDouble(datatype type);
void printDouble(const void *a);
void freeDouble(void *a);