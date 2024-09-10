/*
Assignment name  : add_prime_sum
Expected files   : add_prime_sum.c
Allowed functions: write, exit
--------------------------------------------------------------------------------

Write a program that takes a positive integer as argument and displays the sum
of all prime numbers inferior or equal to it followed by a newline.

If the number of arguments is not 1, or the argument is not a positive number,
just display 0 followed by a newline.

Yes, the examples are right.

Examples:

$>./add_prime_sum 5
10
$>./add_prime_sum 7 | cat -e
17$
$>./add_prime_sum | cat -e
0$
$>
*/
#include <unistd.h>

int         ft_atoi(char *str)
{
    int result; 
    
    while(*str)
        result = result * 10 + *str++ - '0'; 
    return result; 
}
void       ft_putnbr(int n)
{
    char str[] = "0123456789"; 

    if(n > 9)
        ft_putnbr(n / 10); 
    write(1, &str[n % 10], 1); 
}
int is_prime(int n)
{
    if (n < 2)
        return 0; 
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0; 
    }
    return n; 
}
int main(int argc, char **argv)
{
    if (argc == 2)
    {
        int number = ft_atoi(argv[1]);
        if (number <= 0)
        {
            ft_putnbr(0);
            write(1, "\n", 1);
            return 0;
        }

        int sum = 0;
        for (int i = 2; i <= number; i++)
        {
            if (is_prime(i))
                sum += i;
        }
        ft_putnbr(sum);
        write(1, "\n", 1);
    }
    else
    {
        ft_putnbr(0);
        write(1, "\n", 1);
    }

    return 0;
}