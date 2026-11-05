#include "main.h"

/**
 * _memset - fills memory with a constant byte
 * @s: pointeur à la zone mémoire a remplir
 * @b: donnée qui rempli la mémoire
 * @n: nombre de données a remplir
 *
 * Return: pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = b;
	}

	return (s);
}
