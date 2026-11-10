#include <stdio.h>
#include <stdlib.h>

#define D(i, j) d[(i) * (w + 1) + (j)]
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int h, w;
char e, o, x, **g;

int load(FILE *f)
{
    int i, j;

    if (!f || fscanf(f, "%d %c %c %c%*c", &h, &e, &o, &x) != 4
        || h < 1 || e == o || e == x || o == x)
        return -1; // Si no hay archivo, el formato es inválido o los caracteres se repiten, el mapa no es válido.
    g = calloc(h, sizeof(char *)); // Reservamos la matriz de filas del mapa.
    for (i = 0; i < h; i++)
    {
        if (getline(&g[i], &(size_t){0}, f) < 1)
            return -1; // Cada fila debe existir y contener al menos un carácter.
        for (j = 0; g[i][j] == e || g[i][j] == o; j++);
        // Recorremos la fila hasta encontrar el primer carácter que no sea ni vacío ni obstáculo.
        // Así calculamos la anchura real de la fila.
        if (g[i][j] != '\n' || !j || (i && j != w))
            return -1; // La fila debe terminar en salto de línea, no puede estar vacía y todas deben tener la misma longitud.
        g[i][w = j] = 0; // Eliminamos el salto de línea y guardamos la anchura de la fila.
    }
    return 0;
}

void run(FILE *f)
{
    int i, j, *d;
    int size = 0, row = 0, col = 0; // Lado y esquina inferior derecha del mayor cuadrado.

    g = 0;
    if (load(f))
        fprintf(stderr, "map error\n"); // Si el mapa no ha cargado bien, avisamos del error.
    else
    {
        d = calloc((h + 1) * (w + 1), sizeof(int));
        // Tabla DP con una fila y una columna extra a 0 (calloc): así las celdas del borde
        // y los obstáculos no necesitan casos especiales. d[i][j] corresponde a g[i - 1][j - 1].
        for (i = 1; i <= h; i++)
            for (j = 1; j <= w; j++)
            {
                if (g[i - 1][j - 1] == e) // Solo las celdas libres suman; los obstáculos se quedan en 0.
                    D(i, j) = 1 + MIN(MIN(D(i - 1, j), D(i, j - 1)), D(i - 1, j - 1));
                if (D(i, j) > size) // En empate nos quedamos con el primero (arriba a la izquierda).
                {
                    size = D(i, j);
                    row = i - 1;
                    col = j - 1;
                }
            }
        for (i = 0; i < size; i++)
            for (j = 0; j < size; j++)
                g[row - i][col - j] = x; // Rellenamos el cuadrado con el carácter de solución.
        for (i = 0; i < h; i++)
            puts(g[i]); // Imprimimos el mapa final (puts añade el salto de línea).
        free(d);
    }
    for (i = 0; g && i < h; i++)
        free(g[i]); // Liberamos cada fila del mapa para evitar fugas de memoria.
    free(g);
    if (f)
        fclose(f); // Cerramos el archivo si se abrió correctamente.
}

int main(int ac, char **av)
{
    int i;

    if (ac == 1)
        run(stdin); // Si no se pasa archivo, leemos el mapa desde la entrada estándar.
    for (i = 1; i < ac; i++)
    {
        if (i > 1)
            puts(""); // Dejamos una línea en blanco entre varios mapas procesados.
        run(fopen(av[i], "r")); // Abrimos y procesamos cada archivo pasado como argumento.
    }
    return 0;
}