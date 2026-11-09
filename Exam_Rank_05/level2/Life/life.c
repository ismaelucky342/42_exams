#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int w, h;
char *b, *t;                              /* tablero actual y siguiente */

int at(char *m, int y, int x)             /* celda (y,x); fuera del tablero = muerta */
{
	return y >= 0 && y < h && x >= 0 && x < w && m[y * w + x];
}

int main(int ac, char **av)
{
	int n, x = 0, y = 0, pen = 0, dx, dy, k;
	char c, *s;

	if (ac != 4)
		return 1;
	w = atoi(av[1]); h = atoi(av[2]); n = atoi(av[3]);
	b = calloc(w * h, 1);
	t = calloc(w * h, 1);
	while (read(0, &c, 1) > 0)            /* 1. dibujar */
	{
		y -= c == 'w' && y > 0;
		y += c == 's' && y < h - 1;
		x -= c == 'a' && x > 0;
		x += c == 'd' && x < w - 1;
		pen ^= c == 'x';
		b[y * w + x] |= pen;
	}
	while (n--)                           /* 2. simular */
	{
		for (y = 0; y < h; y++)
			for (x = 0; x < w; x++)
			{
				for (k = -at(b, y, x), dy = -1; dy <= 1; dy++)
					for (dx = -1; dx <= 1; dx++)
						k += at(b, y + dy, x + dx);   /* 3x3 menos ella misma */
				t[y * w + x] = k == 3 || (k == 2 && at(b, y, x));
			}
		s = b; b = t; t = s;
	}
	for (y = 0; y < h; y++, putchar('\n')) /* 3. imprimir */
		for (x = 0; x < w; x++)
			putchar(b[y * w + x] ? 'O' : ' ');
	free(b);
	free(t);
	return 0;
}