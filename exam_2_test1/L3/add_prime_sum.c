
int	main(int argc, char *argv[])
{
	int n = atoi(argv[1]);
    int sum = 0;
    for (int i = 2; i <= n; ++i)
    {
        int is_prime = 1;
        for (int j = 2; j * j <= i; ++j)
        {
            if (i % j == 0)
            {
                is_prime = 0;
                break;
            }
        }
        if (is_prime)
            sum += i;
    }
    write(1, &sum, sizeof(sum));
    write(1, "\n", 1);
    return 0;
}
