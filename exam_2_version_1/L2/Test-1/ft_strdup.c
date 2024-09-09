#include <stdlib.h>

int ft_strlen(char *str)
{
    int i = 0; 
    while(str[i])
        i++; 
    return i; 
}
char    *ft_strdup(char *src)
{
    int i = 0; 
    int len = ft_strlen(src); 
    char *cpy = malloc(sizeof(char *)+ len); 

    while(cpy[i])
    {
        while(src[i])
        {
            cpy[i] = src[i]; 
            i++; 
        }
        cpy[i] = '\0'; 
    }
    return cpy; 
}