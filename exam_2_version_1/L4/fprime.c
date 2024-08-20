#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i;
    int number;

    if (argc == 2)
    {
        i = 1; // Initialize the loop counter
        number = atoi(argv[1]); // Convert the input argument from a string to an integer

        // If the number is 1, simply print 1
        if (number == 1)
            printf("1");

        // Loop from 2 upwards to find factors
        while (number >= ++i)
        {
            // If 'i' is a factor of 'number'
            if (number % i == 0)
            {
                printf("%d", i); // Print the factor
                
                // If this factor reduces the number to 1, stop the loop
                if (number == i)
                    break;

                printf("*"); // Print a multiplication symbol to separate factors

                // Divide the number by the factor 'i' to continue factorization
                number /= i;

                // Reset 'i' to start checking for the smallest factor again
                i = 1;
            }
        }
    }

    // Print a newline at the end
    printf("\n");
    return (0);
}

/*
Assignment name  : fprime
Expected files   : fprime.c
Allowed functions: printf, atoi
--------------------------------------------------------------------------------

Write a program that takes a positive int and displays its prime factors on the
standard output, followed by a newline.

Factors must be displayed in ascending order and separated by '*', so that
the expression in the output gives the right result.

If the number of parameters is not 1, simply display a newline.

The input, when there is one, will be valid.

Examples:

$> ./fprime 225225 | cat -e
3*3*5*5*7*11*13$
$> ./fprime 8333325 | cat -e
3*3*5*5*7*11*13*37$
$> ./fprime 9539 | cat -e
9539$
$> ./fprime 804577 | cat -e
804577$
$> ./fprime 42 | cat -e
2*3*7$
$> ./fprime 1 | cat -e
1$
$> ./fprime | cat -e
$
$> ./fprime 42 21 | cat -e
$
*/