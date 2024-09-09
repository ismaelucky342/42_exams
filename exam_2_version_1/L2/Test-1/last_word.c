#include <unistd.h>

int		main(int argc, char **argv)
{
	int i = 0;
    int start = 0; 
    int end = 0; 

	if (argc == 2)
	{
		while (argv[1][i])
			i++;
		while (i > 0 && (argv[1][i - 1] == ' ' || argv[1][i - 1] == '\t'))
			i--;
		end = i;
		while (i > 0 && argv[1][i - 1] != ' ' && argv[1][i - 1] != '\t')
			i--;
		start = i;
		while (start < end)
			write(1, &argv[1][start++], 1);
	}
	write(1, "\n", 1);
	return (0);
}