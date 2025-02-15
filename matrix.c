#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix MatrixInput(){
    Matrix tempMatrix;
    printf("Enter matrix length: ");
    scanf("%d", &tempMatrix.length);
    printf("Enter matrix height: ");
    scanf("%d", &tempMatrix.height);
    tempMatrix.data = realloc(tempMatrix.data, sizeof(Complex) * tempMatrix.height * tempMatrix.length);
    printf("Enter matrix:\n");
    int counter = 0;
    while (counter != (tempMatrix.length * tempMatrix.length)){
        Complex num;
        if(scanf("%lg", &num.real) > 0){
            num.imaginary = 0;
        }
        else if(scanf("(%lg,%lg)", &num.real, &num.imaginary) != 2)
        {
            printf("Error: Invalid format. Try again.\n");
            while (getchar() != '\n');
        }
        tempMatrix.data[counter] = num;
        (tempMatrix.data)++;
        printf("%g %d\n",tempMatrix.data[counter].real, counter);
        counter++;
    }

    return tempMatrix;
}

void MatrixOutput(Matrix matrix){
    for(int i = 0; i < matrix.height; i++){
        for(int j = 0; j < matrix.length; j++){
            if (matrix.data[i+j].imaginary == 0){
                printf("%g ", matrix.data[i+j].real);
            }
            else{
                printf("(%g+%gi) ", matrix.data[i+j].real, matrix.data[i+j].imaginary);
            } 
        }
        printf("\n");
    }
}