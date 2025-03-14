#include <stdio.h>

#include "../inc/matrix.h"
#include "../inc/inputHandling.h"

// TODO: Improve error handling
// TODO: ADD - read command choice until exit
// TODO: ADD - null ptr handling
// TODO: CHECK - double input (complex and mere double)

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
            Matrix *m1 = malloc(sizeof(Matrix));
            Matrix *m2 = malloc(sizeof(Matrix));
            Matrix *result = malloc(sizeof(Matrix));

            printf("\nMatrix addition(A + B)\n");
            printf("--------------------\n");
            printf("First matrix: \n");
            printf("--------------------\n\n");

            if (inputMatrix(m1) == 0)
            {
                freeMatrix(m1);
                freeMatrix(m2);
                freeMatrix(result);
                break;
            }

            printf("\n--------------------\n");
            printf("Enter second matrix: \n");
            printf("--------------------\n\n");

            if (inputMatrix(m2) == 0)
            {
                freeMatrix(m1);
                freeMatrix(m2);
                freeMatrix(result);
                break;
            }

            if (addMatrix(m1, m2, result) == 0)
            {
                printf("Failed to add matrices\n");
            }
            else
            {
                printf("\nResult matrix:\n");
                printf("--------------------\n");
                printMatrix(result);
            }

            freeMatrix(m1);
            freeMatrix(m2);
            freeMatrix(result);
        }
        break;

        case 2: // Matrix multiplication
        {
            Matrix *m1 = malloc(sizeof(Matrix));
            Matrix *m2 = malloc(sizeof(Matrix));
            Matrix *result = malloc(sizeof(Matrix));
            printf("\nMatrix Multiplication (A × B)\n");
            printf("--------------------\n");
            printf("First matrix: \n");
            printf("--------------------\n\n");

            if (inputMatrix(m1) == 0)
            {
                freeMatrix(m1);
                freeMatrix(m2);
                freeMatrix(result);
                break;
            }

            printf("\n--------------------\n");
            printf("Enter second matrix: \n");
            printf("--------------------\n\n");

            if (inputMatrix(m2) == 0)
            {
                freeMatrix(m1);
                freeMatrix(m2);
                freeMatrix(result);
                break;
            }

            if (multiplyMatrix(m1, m2, result) == 0)
            {
                printf("Failed to multiply matrices\n");
            }
            else
            {
                printf("\nResult matrix:\n");
                printf("--------------------\n");
                printMatrix(result);
            }

            freeMatrix(m1);
            freeMatrix(m2);
            freeMatrix(result);
        }
        break;
            break;
        case 3: // Matrix transposition
        {
            Matrix *m = malloc(sizeof(Matrix));
            printf("\nMatrix Transposition\n");
            printf("--------------------\n");
            printf("Enter matrix: \n");
            printf("--------------------\n\n");

            if (inputMatrix(m) == 0)
            {
                freeMatrix(m);
                break;
            }

            if (transportMatrix(m) == 0)
            {
                printf("Failed to transpose matrix\n");
            }
            else
            {
                printf("\nTransposed matrix:\n");
                printf("--------------------\n");
                printMatrix(m);
            }

            freeMatrix(m);
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

/*
Add
(1,2) (3, -1)
(0,4) (5,6)

(2, -1) (1, 3)
(0,-2) (3, -4)


Multi
(1,1) (2,-3)
(0, 3) (4, 2)

(2,-1) (1,2)
(-1, 1) (3, -1)

*/