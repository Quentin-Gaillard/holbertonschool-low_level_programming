#include "main.h"

/**
 * swap_int - Swaps the values of two integers. With a temporary glass.
 * @a: A pointer to the first integer.
 * @b: A pointer to the second integer.
 *
 * Return: void.
 */
void swap_int(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
