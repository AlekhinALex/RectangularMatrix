#pragma once

#include "matrix.h"

int getChoice(int minBorder, int maxBorder);
unsigned int inputDimension();
void invalidInput();
void createNewMatrix(unsigned int height, unsigned int length, const typeInfo *type, Matrix *matrix);
void setupMatrix(int height, int length, const typeInfo *type, Matrix *matrix);