#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "complex.h"
#include "matrix.h"

int main()
{
    int choice = 0;
    char *command = NULL;
    size_t command_size = 0;
    char *chk_command;

    printf("=========================================================\n");
    printf("\tMenu\n");
    printf("=========================================================\n");
    printf("1) Sum of two matrices\n");
    printf("2) Multiplication of two matrices\n");
    printf("3) Matrix transposition\n");
    printf("4) Adding a linear combination of other strings to a string\n");
    printf("5) Exit\n\n");

    // Checkig if entered string is a number
    do
    {
        printf("Enter a number to select an action: ");
        ssize_t n_chars_command = getline(&command, &command_size, stdin);
        choice = (int)strtol(command, &chk_command, 10);
        if (!isspace(*chk_command) && *chk_command != 0 || (choice > 5) || (choice < 1))
        {
            printf("Error: Invalid input. Try again.\n");
        }
    } while (!isspace(*chk_command) && *chk_command != 0 || (choice > 5) || (choice < 1));

    switch (choice)
    {
    case 1: // Matrix + Matrix
    {
        Matrix mat1_1 = {0, 0, NULL};
        Matrix mat2_1 = {0, 0, NULL};
        Matrix matSum_1 = {0, 0, NULL};
        while (1)
        {
            printf("\nMatrix addition(A + B)\n");
            printf("--------------------\n");
            printf("Enter first matrix: \n");
            printf("--------------------\n");
            mat1_1 = MatrixInput();
            printf("\n--------------------\n");
            printf("Enter second matrix: \n");
            printf("--------------------\n");
            mat2_1 = MatrixInput();
            if (mat1_1.length != mat2_1.length || mat1_1.height != mat2_1.height)
            {
                printf("\n=========================================================\n");
                printf("Error: Matrices must have identicals sizes. Try again.\n");
                printf("=========================================================\n");
                MatrixFree(&mat1_1);
                MatrixFree(&mat2_1);
                continue;
            }
            else
            {
                break;
            }
        }

        matSum_1 = MatrixSum(mat1_1, mat2_1);
        printf("\n--------------------\n");
        printf("Result matrix:\n");
        printf("--------------------\n");

        MatrixOutput(matSum_1);

        MatrixFree(&mat1_1);
        MatrixFree(&mat2_1);
        MatrixFree(&matSum_1);
    }
    break;
    case 2:
    {
        Matrix mat1_2 = {0, 0, NULL};
        Matrix mat2_2 = {0, 0, NULL};
        Matrix matMulti = {0, 0, NULL};
        while (1)
        {
            printf("\nMatrix Multiplication (A × B)\n");
            printf("--------------------\n");
            printf("Enter first matrix: \n");
            printf("--------------------\n");
            mat1_2 = MatrixInput();
            printf("\n--------------------\n");
            printf("Enter second matrix: \n");
            printf("--------------------\n");
            mat2_2 = MatrixInput();
            if (mat1_2.length != mat2_2.height)
            {
                printf("\n=========================================================\n");
                printf("Error: The number of columns of the first matrix must be\nequal to the number of rows of the second matrix.\nTry again.\n");
                printf("=========================================================\n");
                MatrixFree(&mat1_2);
                MatrixFree(&mat2_2);
                continue;
            }
            else
            {
                break;
            }
        }

        matMulti = MatrixMultiplyByMatrix(mat1_2, mat2_2);

        printf("\n--------------------\n");
        printf("Result matrix:\n");
        printf("--------------------\n");

        MatrixOutput(matMulti);

        MatrixFree(&mat1_2);
        MatrixFree(&mat2_2);
        MatrixFree(&matMulti);
    }
    break;
    case 3: // Matrix transposition
    {
        Matrix mat3 = MatrixInput();
        MatrixOutput(mat3);
        MatrixFree(&mat3);
        break;
    }
    case 4:
        break;

    case 5:
        break;
    default:
        printf("Unexpected error: Invalid choice.\n");
        break;
    }
    free(command);
    return 0;
}
