#include "main.h"

/**
 * _memcpy - copies memory area
 * @dest: montre le dépot de destination
 * @src: montre la source des objets a copier dans le dépot.
 * @n: nombre des objets a copier
 *
 * Return: pointer to dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}

	return (dest);
}
