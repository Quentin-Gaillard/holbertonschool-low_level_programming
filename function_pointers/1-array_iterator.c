#include "function_pointers.h"

/**
 * array_iterator - executes a function on each element of an array
 * @array: pointeur sur la premier case du tableau
 * @size: nombre d'éléments dans le tableau
 * @action: pointeur de la fonction qui s'exécute a chaque élément
 *
 * Return: Nothing.
 */



void array_iterator(int *array, size_t size, void (*action)(int))
{
	size_t i;

	if (array == NULL || action == NULL)
		return;

	for (i = 0; i < size; i++)
	{
		action(array[i]);
	}


