int		ft_strlen(char *str)
{
	int i = 0; 

	while(str[i])
		i++;
	return i; 
}

char    *ft_strrev(char *str)
{
    int inicio = 0;
    int fin = ft_strlen(str) - 1;
    char temp;

    while (inicio < fin)
    {
        temp = str[inicio];
        str[inicio] = str[fin];
        str[fin] = temp;
        inicio++;
        fin--;
    }

    return str;
}