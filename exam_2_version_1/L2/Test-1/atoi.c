#include <unistd.h>

int	ft_atoi(const char *str)
{
    int sign = 1; 
    int result = 0;

    while (*str == ' ' || (*str >= 9 && *str <= 13))
        	str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;

    while(*str >= '0' && *str <= '9')
        result = result * 10 + *str++ - '0'; 
    return (result *sign); 
}