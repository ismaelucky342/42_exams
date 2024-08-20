#include <stdio.h>
#include <stdlib.h>

// Function to convert an integer to a string
char *ft_itoa(int nbr) 
{
    // Special case: handle the smallest integer value (-2147483648) directly
    if(nbr == -2147483648)
        return("-2147483648\0");

    int n = nbr;  // Temporary variable to determine the number of digits
    int len = 0;  // Variable to hold the length of the result string

    // If the number is negative or zero, account for the sign or '0' character
    if (nbr <= 0)
        len++;
    
    // Determine the length of the string needed by counting digits
    while (n) 
    {
        n /= 10;
        len++;
    }

    // Allocate memory for the result string (+1 for the null terminator)
    char *result = (char *)malloc(sizeof(char) * (len + 1));
    if (result == NULL) 
        return NULL; // Return NULL if memory allocation fails
    
    result[len] = '\0';  // Null-terminate the string
    
    // Special case for zero
    if (nbr == 0)
    {
        result[0] = '0';  // Set the only character to '0'
        return result;
    }
    
    // If the number is negative, add the '-' sign and make the number positive
    if (nbr < 0) 
    {
        result[0] = '-';
        nbr = -nbr;
    }
    
    // Convert the number to a string, starting from the end of the allocated buffer
    while (nbr) 
    {
        result[--len] = nbr % 10 + '0';  // Extract the last digit and convert it to a character
        nbr /= 10;  // Remove the last digit from the number
    }

    return result;  // Return the result string
}

/*
Assignment name  : ft_itoa
Expected files   : ft_itoa.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Write a function that takes an int and converts it to a null-terminated string.
The function returns the result in a char array that you must allocate.

Your function must be declared as follows:

char	*ft_itoa(int nbr);
*/