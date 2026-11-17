#include "function_pointers.h"

/**
 * int_index - searches for an integer in an array using a comparison function
 * @array: pointer vers le tableau de nombres entiesr
 * @size: nombred 'éléments dans le tableau
 * @cmp: pointeur vers la fonction qui COMPARE (cmp) les valeurs
 *
 * Return: Index of the first matching element, or -1 if no match or error.
 */

int int_index(int *array, int size, int (*cmp)(int))
{
	int i;

	if (array == NULL || cmp == NULL || size <= 0)
		return (-1);

	for (i = 0; i < size; i+)
	{
		if (cmp(array[i]) != 0)
			return (i);
	}

	return (-1);
}

