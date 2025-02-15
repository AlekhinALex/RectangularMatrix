#pragma once
typedef struct Complex
{
  double imaginary;
  double real;
}Complex;

void ComplexInput(Complex* num);
void ComplexOutput(Complex num);