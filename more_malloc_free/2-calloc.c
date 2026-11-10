#include "main.h"
#include <stdlib.h>

/**
 * _calloc - Alloue de la mémoire pour un tableau et l'initialise à zéro.
 * @nmemb: Nombre d'éléments dans le tableau.
 * @size: Taille en octets de chaque élément.
 *
 * Return: Un ptr vers la mémoire allouée, ou NULL si échec ou taille nulle.
 */

void *_calloc(unsigned int nmemb, unsigned int size)
{
	void *ptr;
	char *filler;
	unsigned int total_size, i;

	if (nmemb == 0 || size == 0)
	{
		return (NULL);
	}
	total_size = nmemb * size;

	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);

	filler = ptr;
	for (i = 0; i < total_size; i++)
	*filler++ = 0;

	return (ptr);
}
