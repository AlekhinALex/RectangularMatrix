#include <stdio.h>
#include <stdlib.h>

#include "../inc/matrix.h"
#include "../inc/inputHandling.h"
#include "../inc/errorHandling.h"

// TODO: !MB! in input make the second input with definite type
void printMenu();

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

            printf("\nMatrix addition(A + B)\n");
            printf("--------------------\n");
            printf("First matrix: \n");
            printf("--------------------\n\n");

            if (inputNewMatrix(&m1) == ERROR_OCCURRED)
            {
                break;
            }

            printf("\n--------------------\n");
            printf("Enter second matrix: \n");
            printf("--------------------\n\n");

            if (inputNewMatrix(&m2) == ERROR_OCCURRED)
            {
                freeMatrix(&m1);
                break;
            }

            if (addMatrix(&m1, &m2, &result) == ERROR_OCCURRED)
            {
                freeMatrix(&m1);
                freeMatrix(&m2);
                printf("Failed to add matrices\n\n");
            }
            else
            {
                printf("\nResult matrix:\n");
                printf("--------------------\n");
                printMatrix(&result);
                freeMatrix(&m1);
                freeMatrix(&m2);
                freeMatrix(&result);
            }
        }
        break;

        case 2: // Matrix multiplication
        {
            Matrix m1;
            Matrix m2;
            Matrix result;
            printf("\nMatrix Multiplication (A × B)\n");
            printf("--------------------\n");
            printf("First matrix: \n");
            printf("--------------------\n\n");

            if (inputNewMatrix(&m1) == ERROR_OCCURRED)
            {
                break;
            }

            printf("\n--------------------\n");
            printf("Enter second matrix: \n");
            printf("--------------------\n\n");

            if (inputNewMatrix(&m2) == ERROR_OCCURRED)
            {
                freeMatrix(&m1);
                break;
            }

            if (multiplyMatrix(&m1, &m2, &result) == ERROR_OCCURRED)
            {
                freeMatrix(&m1);
                freeMatrix(&m2);
                printf("Failed to multiply matrices\n\n");
            }
            else
            {
                printf("\nResult matrix:\n");
                printf("--------------------\n");
                printMatrix(&result);
                freeMatrix(&m1);
                freeMatrix(&m2);
                freeMatrix(&result);
            }
        }
        break;
        case 3: // Matrix transposition
        {
            Matrix m;
            printf("\nMatrix Transposition\n");
            printf("--------------------\n");
            printf("Enter matrix: \n");
            printf("--------------------\n\n");

            if (inputNewMatrix(&m) == ERROR_OCCURRED)
            {
                break;
            }

            if (transposeMatrix(&m) == ERROR_OCCURRED)
            {
                printf("Failed to transpose matrix\n\n");
            }
            else
            {
                printf("\nTransposed matrix:\n");
                printf("--------------------\n");
                printMatrix(&m);
                freeMatrix(&m);
            }
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
