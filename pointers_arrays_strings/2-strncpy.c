#include "main.h"

/**
 * _strncpy - Copie une chaîne de caractères jusqu'à n octets
 * @dest: Pointeur vers la chaîne de destination
 * @src: Pointeur vers la chaîne source
 * @n: Nombre maximal d'octets à copier
 *
 * Return: Pointeur vers dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	for (; i < n; i++)
	{
		dest[i] = '\0';
	}

	return (dest);
}
