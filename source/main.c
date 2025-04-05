#include <stdio.h>
#include <stdlib.h>

#include "../inc/complex.h"
#include "../inc/integer.h"
#include "../inc/double.h"
#include "../inc/matrix.h"

#include "../inc/inputHandling.h"
#include "../inc/errorHandling.h"

void printMenu();
void determineElemType(Matrix *matrix);
void enterDims(Matrix *matrix);
void printEnteringRules(Matrix *matrix);

int main()
{
    int choice;
    int continueToWork = 1;
    while (continueToWork)
    {
        printMenu();
        choice = getChoice(1, 4);

        switch (choice)
        {
        case 1: // Matrix addition
        {
            Matrix m1;
            Matrix m2;
            Matrix result;

            printf("Matrix addition(A + B)\n");

            enterDims(&m1);
            determineElemType(&m1);

            printEnteringRules(&m1);

            createNewMatrix(m1.height, m1.height, m1.typeInfo, &m2);
            createNewMatrix(m1.height, m1.height, m1.typeInfo, &result);

            if (readMatrixComponents(&m1) == SUCCESSFUL_EXECUTION &&
                readMatrixComponents(&m2) == SUCCESSFUL_EXECUTION)
            {

                if (addMatrix(&m1, &m2, &result) == ERROR_OCCURRED)
                {
                    printf("Failed to add matrices\n");
                }
                else
                {
                    printf("Result matrix:\n");
                    printMatrix(&result);
                }
            }

            removeInternal(&m1);
            removeInternal(&m2);
            removeInternal(&result);
        }
        break;

        case 2: // Matrix multiplication
        {
            Matrix m1, m2, result;

            printf("Matrix Multiplication (A × B)\n");

            enterDims(&m1);
            determineElemType(&m1);
            printEnteringRules(&m1);

            if (readMatrixComponents(&m1) == SUCCESSFUL_EXECUTION)
            {
                m2.typeInfo = m1.typeInfo;

                enterDims(&m2);
                createNewMatrix(m2.height, m2.length, m2.typeInfo, &m2);

                if (readMatrixComponents(&m2) == SUCCESSFUL_EXECUTION)
                {
                    createNewMatrix(m1.height, m2.length, m1.typeInfo, &result);

                    if (multiplyMatrix(&m1, &m2, &result) == SUCCESSFUL_EXECUTION)
                    {
                        printf("Result matrix:\n");
                        printMatrix(&result);
                    }
                    else
                    {
                        printf("Failed to multiply matrices\n\n");
                    }
                }
            }

            removeInternal(&m1);
            removeInternal(&m2);
            removeInternal(&result);
        }
        break;
        case 3: // Matrix transposition
        {
            Matrix m;

            printf("Matrix Transposition\n");

            enterDims(&m);
            determineElemType(&m);

            if (readMatrixComponents(&m) == SUCCESSFUL_EXECUTION)
            {
                if (transposeMatrix(&m) == ERROR_OCCURRED)
                {
                    printf("Failed to transpose matrix\n\n");
                }
                else
                {
                    printf("Tansposed matrix:\n");
                    printMatrix(&m);
                }
            }

            removeInternal(&m);
        }
        break;
        case 4:
            continueToWork = 0;
            break;
        default:
            printf("Unexpected error: Invalid choice.\n");
            break;
        }
    }
    return 0;
}

void printMenu()
{
    printf("=========================================================\n");
    printf("\tMenu\n");
    printf("=========================================================\n");
    printf("1) Sum of two matrices\n");
    printf("2) Multiplication of two matrices\n");
    printf("3) Matrix transposition\n");
    printf("4) Exit\n\n");
}

void determineElemType(Matrix *matrix)
{
    int typeHolder;

    printf("Enter what types of data will be stored:\n");
    printf("1) Real numbers\n");
    printf("2) Integers\n");
    printf("3) Complex numbers\n");

    typeHolder = getChoice(1, 3);

    const typeInfo *type;
    switch (typeHolder)
    {
    case 1:
        type = getTypeInfoDouble();
        break;
    case 2:
        type = getTypeInfoInteger();
        break;
    case 3:
        type = getTypeInfoComplex();
        break;
    default:
        type = NULL;
        break;
    }

    matrix->typeInfo = type;
    matrix->data = malloc(matrix->height * matrix->length * matrix->typeInfo->size());
}

void enterDims(Matrix *matrix)
{
    int height, length;
    printf("\nMatrix Size\n");
    printf("-----------\n");
    printf("Remember, the matrix dimensions must be greater than zero.\n");

    printf("Enter matrix height: ");
    height = inputDimension();

    printf("Enter matrix length: ");
    length = inputDimension();

    matrix->height = height;
    matrix->length = length;
}

void printEnteringRules(Matrix *matrix)
{
    printf("\nInput rules:\n");

    if (matrix->typeInfo == getTypeInfoDouble())
    {
        printf("Enter real numbers (e.g., 5.2)\n");
    }
    else if (matrix->typeInfo == getTypeInfoInteger())
    {
        printf("Enter integer numbers (e.g., 5)\n");
    }
    else if (matrix->typeInfo == getTypeInfoComplex())
    {
        printf("Enter complex numbers (e.g., (5, 3) or (3.6, 9) )\n");
    }
}