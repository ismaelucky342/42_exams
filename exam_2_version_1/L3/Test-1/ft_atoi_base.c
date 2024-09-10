#include <unistd.h>

int ft_value(char c)
{
    if (c >= '0' || c <= '9')
        return(c - '0'); 
    else if (c >= 'a' || c <= 'f')
        return(c - 'a' + 10);
    else if (c >= 'A' || c <= 'F')
        return(c - 'A' + 10);
    return -1; 

}

int	ft_atoi_base(const char *str, int str_base)
{
    if (str_base < 2 || str_base > 16) 
        return 0;

    int result = 0;
    int sign = 1; 

    while(*str == ' ' || (*str >= 9 && *str <= 13 ))
        str++;
    if ( *str == '-') 
        sign = -1;
    if ( *str == '-' || *str == '+')
        str++; 

    while (*str)
    {
        int value = ft_value(*str); 

        if (value < 0 || value >= str_base)
            break; 
        result = result * str_base + value; 
        str++; 
    }
    return (result * sign);     
}
