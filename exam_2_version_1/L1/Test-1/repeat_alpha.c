#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int repeticiones;
    
    if(argc == 2)
    {
        i = 0;
        while (argv[1][i])
        {
            if (argv[1][i] >= 'a' && argv[1][i] <= 'z') 
                repeticiones = argv[1][i] - 'a' + 1;
            else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
            repeticiones = argv[1][i] - 'A' + 1;
            else 
                repeticiones = 1; 

            while(repeticiones--)
                write(1, &argv[1][i], 1);
            i++; 
        }
    }
    write(1, "\n", 1);
}