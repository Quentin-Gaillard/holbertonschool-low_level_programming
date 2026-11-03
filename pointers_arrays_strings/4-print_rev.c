#include "main.h"

/**
 * print_rev - Prints a string, in reverse, followed by a new line.
 * @s: A pointer to the string to print.
 * ici on doit partir au bout de la phrase pour compter et ensuite revenir au débit.
 * Return: void.
 */
void print_rev(char *s)
{
	int len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}

	len--;
	while (len >= 0)
	{
		_putchar(s[len]);
		len--;
	}
	_putchar('\n');
}
