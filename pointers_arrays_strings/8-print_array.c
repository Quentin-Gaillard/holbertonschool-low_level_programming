#include "main.h"
#include <stdio.h>

/**
 * print_array - indique n éléments d'un tableau d'entiers
 * @a = pointeur du premier élément du tableau (array)
 * @n = le nombre d'éléments à indiquer (print)
 *
 * Return void
 */
void print_array(int *a, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		printf("%d", a[i]);

		if (i < n - 1)
		{
			printf(", ");
		}
	}
	printf("\n");
}
