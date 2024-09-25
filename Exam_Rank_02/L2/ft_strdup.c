 /*Assignment name  : ft_strdup
Expected files   : ft_strdup.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Reproduce the behavior of the function strdup (man strdup).

Your function must be declared as follows:

char    *ft_strdup(char *src);
*/
#include <stdlib.h>
//#include <stdio.h>

int		ft_strlen(char *str)
{
	int i = 0; 

	while(str[i])
		i++; 
	return i; 
}

char    *ft_strdup(char *src)
{
	int i = 0; 
	char *copia;
	int len = ft_strlen(src) + 1; 
	
	copia = malloc(sizeof(*copia) * len); 
	
	if(copia)
	{
		while(src[i])
		{
			copia[i] = src[i]; 
			i++; 
		}
		copia[i] = '\0'; 
	} 
	return (copia); 
}
/*
int main()
{
	char str[] = "holamundo";
	
	printf("cadena original: %s\n cadena duplicada: %s\n", str, ft_strdup(str));

	return 0; 
}
*/