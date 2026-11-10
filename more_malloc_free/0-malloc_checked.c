#include "main.h"
#include <stdlib.h>

/**
 * malloc_checked - Alloue de la mémoire en utilisant malloc.
 * @b: Le nombre d'octets à allouer avec 4 tests.
 *
 * Return: Un pointeur vers la mémoire allouée.
 *         Si malloc échoue, le programme s'arrête avec le statut 98.
 *	C'est un bouton rouge d'arrêt d'urgence.
 */
void *malloc_checked(unsigned int b)
{
	void *ptr;

	ptr = malloc(b);

	if (ptr == NULL)
	{
		exit(98);
	}

	return (ptr);
}
