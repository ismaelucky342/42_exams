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
        return -1;
    g = calloc(h, sizeof(char *));
    for (i = 0; i < h; i++)
    {
        if (getline(&g[i], &(size_t){0}, f) < 1)
            return -1;
        for (j = 0; g[i][j] == e || g[i][j] == o; j++);
        if (g[i][j] != '\n' || !j || (i && j != w))
            return -1;
        g[i][w = j] = 0;
    }
    return 0;
}

void run(FILE *f)
{
    int i, j, p = 0, *d;

    g = 0;
    if (load(f))
        fprintf(stderr, "map error\n");
    else
    {
        d = calloc(h * w, sizeof(int));
        for (i = 0; i < h; i++)
            for (j = 0; j < w; j++)
            {
                D(i, j) = g[i][j] == o ? 0 : (!i || !j) ? 1
                    : 1 + MIN(MIN(D(i - 1, j), D(i, j - 1)), D(i - 1, j - 1));
                if (D(i, j) > d[p])
                    p = i * w + j;
            }
        for (i = 0; i < d[p] * d[p]; i++)
            g[p / w - i / d[p]][p % w - i % d[p]] = x;
        for (i = 0; i < h; i++)
            fprintf(stdout, "%s\n", g[i]);
        free(d);
    }
    for (i = 0; g && i < h; i++)
        free(g[i]);
    free(g);
    if (f)
        fclose(f);
}

int main(int ac, char **av)
{
    int i;

    if (ac == 1)
        run(stdin);
    for (i = 1; i < ac; i++)
    {
        if (i > 1)
            fputs("\n", stdout);
        run(fopen(av[i], "r"));
    }
    return 0;
}