#include <unistd.h>

void	ft_putnbr(int n)
{
	char nbr[] = "0123456789";
	if (n > 9)
		ft_putnbr(n / 10);
	write(1, &nbr[n % 10], 1);
}

int	main(void)
{
	int i = 1;
	while (i <= 100)
	{
		if (i % 15 == 0)
			write(1, "fizzbuz", 8);
		else if (i % 3 == 0)
			write(1, "fizz", 4);
		else if (i % 5 == 0)
			write(1, "buzz", 4);
        else 
            ft_putnbr(i); 
        write(1, "\n", 1); 
        i++; 
	}
}