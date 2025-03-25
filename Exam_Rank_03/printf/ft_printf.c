#include <unistd.h>
#include <stdarg.h>

int putstr(char *s, int count)
{
	if (!s)
		s = "(null)";
	while (*s)
		count += write(1, s++, 1);
	return count;
}

int putnum(long num, int base)
{
	char *digits = "0123456789abcdef";
	int count = 0;

	if (num < 0 && base == 10)
	{
		count += write(1, "-", 1);
		num = -num;
	}
	else if (num < 0 && base == 16)
		num = (unsigned int)num;
	
    if (num >= base)
		count += putnum(num / base, base);
	count += write(1, &digits[num % base], 1);

	return count;
}

int ptf(char *s, va_list args, int i, int n)
{
	if (!s[i])
		return n;
	if (s[i] == '%' && s[i + 1] == 's')
		return ptf(s, args, i + 2, n + putstr(va_arg(args, char *), 0));
	if (s[i] == '%' && s[i + 1] == 'd')
		return ptf(s, args, i + 2, n + putnum(va_arg(args, int), 10));
	if (s[i] == '%' && s[i + 1] == 'x')
		return ptf(s, args, i + 2, n + putnum(va_arg(args, int), 16));
	return ptf(s, args, i + 1, n + write(1, &s[i], 1));
}

int ft_printf(char *s, ...)
{
	va_list args;
	return va_start(args, s), va_end(args), ptf(s, args, 0, 0);
}