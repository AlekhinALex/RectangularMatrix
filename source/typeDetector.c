#include <stdio.h>
#include "../inc/integer.h"
#include "../inc/complex.h"
#include "../inc/double.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 100

int main()
{
    char buffer[BUFFER_SIZE];
    printf("Enter a number: ");
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
    {
        perror("Error reading input");
        return 1;
    }

    // Remove trailing newline (if any)
    buffer[strcspn(buffer, "\n")] = '\0';

    // Try parsing as an integer
    char *endptr;
    errno = 0;
    long int_value = strtol(buffer, &endptr, 10);

    if (errno == 0 && *endptr == '\0')
    {
        printf("You entered an integer: %ld\n", int_value);
    }
    else
    {
        // Try parsing as a double
        errno = 0;
        double double_value = strtod(buffer, &endptr);

        if (errno == 0 && *endptr == '\0')
        {
            printf("You entered a double: %lf\n", double_value);
        }
        else
        {
            printf("Invalid input: not an integer or double.\n");
        }
    }

    return 0;
}