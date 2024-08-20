
/*
Assignment name  : union
Expected files   : union.c
Allowed functions: write
--------------------------------------------------------------------------------

Escriba un programa que tome dos cadenas y muestre, sin dobles, el
caracteres que aparecen en cualquiera de las cadenas.

La pantalla se mostrará en el orden en que aparecen los caracteres en la línea de comando y
irá seguido de un \n.

Si el número de argumentos no es 2, el programa muestra \n.

$>./union zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
zpadintoqefwjy$
$>./union ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6vewg4thras$
$>./union "rien" "cette phrase ne cache rien" | cat -e
rienct phas$
$>./union | cat -e
$
$>
$>./union "rien" | cat -e
$
$>
*/
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
                // Recorre la segunda cadena para verificar si el carácter está presente.
                for (int j = 0; argv[2][j]; j++)
                {
                    if (argv[1][i] == argv[2][j])
                    {
                        write(1, &argv[1][i], 1); // Muestra el carácter.
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