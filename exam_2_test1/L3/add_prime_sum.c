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

int	ft_atoi(char *s)
{
	int	res = 0;
	while (*s)
		res = res * 10 + *s++ - '0';
	return (res);
}

int	is_prime(int num)
{
	if (num <= 1)
		return (0);
	for (int i = 2; i * i <= num; i++)
		if (num % i == 0)
			return (0);
	return (1);
}

void	put_nbr(int n)
{
	if (n >= 10)
		put_nbr(n / 10);
	char digit = n % 10 + '0';
	write(1, &digit, 1);
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		int	nbr = ft_atoi(av[1]);
		int	sum = 0;
		while (nbr > 0)
			if (is_prime(nbr--))
				sum += nbr + 1;
		put_nbr(sum);
	}
	else
		put_nbr(0);
	write(1, "\n", 1);
	return (0);
}
