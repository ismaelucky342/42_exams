#include <unistd.h>

int main(int ac, char **av)
{
    unsigned char seen[256] = {0};
    
    if (ac == 3)
    {
        for (int i = 0; av[1][i]; i++)//que rico que no hay norma papi
        {
            for (int j = 0; av[2][j]; j++)
            {
                if (av[1][i] == av[2][j] && !seen[(unsigned char)av[1][i]])
                {
                    write(1, &av[1][i], 1);
                    seen[(unsigned char)av[1][i]] = 1;
                    break;
                }
            }
        }
    }
    
    write(1, "\n", 1);
    return 0;
}
