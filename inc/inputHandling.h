#pragma once

#include "matrix.h"

int getChoice(int minBorder, int maxBorder);
unsigned int inputDimension();
void invalidInput();
void clearInputBuffer();
Matrix createNewMatrix(int height, int length, int typeHolder);
Matrix setupMatrix(int height, int length, const TypeInfo *type);