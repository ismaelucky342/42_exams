#include <stdio.h>
#include <stdlib.h>

#define D(i, j) d[(i) * w + (j)]
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int h, w;
char e, o, x, **g;

int load(FILE *f)
{
    int i, j;

    if (!f || fscanf(f, "%d %c %c %c%*c", &h, &e, &o, &x) != 4
        || h < 1 || e == o || e == x || o == x)
        return -1; // Si no hay archivo, el formato es inválido o los caracteres se repiten, la mapa no es válido.
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
    int i, j, p = 0, *d;

    g = 0;
    if (load(f))
        fprintf(stderr, "map error\n"); // Si el mapa no ha cargado bien, avisamos del error.
    else
    {
        d = calloc(h * w, sizeof(int)); // Reserva la tabla DP para guardar el tamaño del cuadrado más grande que termina en cada celda.
        for (i = 0; i < h; i++)
            for (j = 0; j < w; j++)
            {
                D(i, j) = g[i][j] == o ? 0 : (!i || !j) ? 1
                    : 1 + MIN(MIN(D(i - 1, j), D(i, j - 1)), D(i - 1, j - 1));
                // Si la celda es un obstáculo, vale 0; si es libre, calcula la longitud máxima del cuadrado que termina aquí.
                // Se usa la fórmula clásica del algoritmo del cuadrado máximo.
                if (D(i, j) > d[p])
                    p = i * w + j; // Guardamos la posición del mayor cuadrado encontrado hasta ahora.
            }
        for (i = 0; i < d[p] * d[p]; i++)
            g[p / w - i / d[p]][p % w - i % d[p]] = x;
        // Recorremos todos los puntos del cuadrado más grande y los rellenamos con el carácter de solución.
        for (i = 0; i < h; i++)
            fprintf(stdout, "%s\n", g[i]); // Imprimimos cada fila del mapa final con la solución marcada.
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
            fputs("\n", stdout); // Dejamos una línea en blanco entre varios mapas procesados.
        run(fopen(av[i], "r")); // Abrimos y procesamos cada archivo pasado como argumento.
    }
    return 0;
}