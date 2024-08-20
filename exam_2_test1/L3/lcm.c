

unsigned int	lcm(unsigned int a, unsigned int b)
{
	if (a == 0 || b == 0)
		return (0);
	unsigned int	tempA = a;
	unsigned int	tempB = b;
	while (tempB != 0)
	{
		unsigned int	temp = tempB;
		tempB = tempA % tempB;
		tempA = temp;
	}
	return ((a * b) / tempA);
}

int	main()
{
	unsigned int	num1 = 6;
	unsigned int	num2 = 8;
	unsigned int	result = lcm(num1, num2);

	printf ("EL mcm de %u y %u es %u\n", num1, num2, result);
	return (0);
}