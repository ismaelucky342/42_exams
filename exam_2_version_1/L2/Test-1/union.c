#include <stdio.h>

int main(int argc, char **argv)
{
    if(argc == 3)
    {
        int seen[256] = {0}; 

        for(int i = 0; argv[1][i]; i++)
        {
            if (!seen[(unsigned char)argv[1][i]]) // Verifica si el carácter aún no se ha mostrado.
            {
                for (int j = 0; argv[2][j]; j++)
                {
                    if (argv[1][i] == argv[2][j])
                    {
                        write(1, &argv[1][i++], 1); // Muestra el carácter.
                        seen[(unsigned char)argv[1][i]] = 1; // Marca el carácter como mostrado.
                        break; // Sale del bucle interno para evitar mostrar el carácter nuevamente.
                    }
                }
            }
        }

	}
    write(1, "\n", 1); 
    return 0; 
}