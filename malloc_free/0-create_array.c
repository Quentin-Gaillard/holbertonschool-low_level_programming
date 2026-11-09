#include "main.h"
#include <stdlib.h>

/**
 * create_array - Crée un tableau de caractères et l'initialise
 *                avec un caractère spécifique.
 * @size: La taille du tableau à allouer.
 * @c: Le caractère d'initialisation.
 *
 * Return: Un pointeur vers le tableau alloué,
 *         ou NULL si size vaut 0 ou si l'allocation échoue.
 */
char *create_array(unsigned int size, char c)
{
	char *array;
	unsigned int i;

	if (size == 0)
	{
		return (NULL);
	}

	array = malloc(size * sizeof(char));

	if (array == NULL)
	{
		return (NULL);
	}

	i = 0;
	{
		array[i] = c;
		i++;
	}

	return (array);
}
