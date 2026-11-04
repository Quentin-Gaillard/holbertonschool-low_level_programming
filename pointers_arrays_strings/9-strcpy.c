#include "main.h"

/**
 * _strcpy - copie de chaine pointée par src dans le tampon pointé par dest
 * @dest: pointeur vers le tampon (buffer)
 * @src: pointeur vers la chaine de caractere source
 *
 * Return: le pointeur vers dest.
 */

 char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}
