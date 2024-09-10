#include <stdlib.h>

int     *ft_range(int start, int end)
{
    int i = 0; 
    int *result; 
    int len = (end - start) + 1;

    if(!(result = malloc(sizeof(int)*len)))
        return '\0';
    while(i < len)
    {
        if (end > start)
        {
            result[i] = end; 
            i--; 
        }
        else
        {
            result[i] = end; 
            i++; 
        }
    }
    return result; 
}