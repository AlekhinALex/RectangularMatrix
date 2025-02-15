#include <stdio.h>
#include "complex.h"

void ComplexInput(Complex *num)
{
    printf("Enter complex number like in template (real, imaginary)\n");
    while (scanf("(%lg,%lg)", &num->real, &num->imaginary) != 2)
    {
        printf("Error: Invalid format. Try again.\n");
        while (getchar() != '\n')
            ;
    }
}

void ComplexOutput(Complex num)
{
    printf("%g+%gi ", num.real, num.imaginary);
}