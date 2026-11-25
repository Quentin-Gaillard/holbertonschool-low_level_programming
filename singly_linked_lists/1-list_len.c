#include <stddef.h>
#include "lists.h"

/**
 * list_len - returns the number of elements in a linked list_t list
 * @h: pointer to the first node of the list
 *
 * Return: the number of nodes in the list
 */
size_t list_len(const list_t *h)
{
	const list_t *current;
	size_t count;

	current = h;
	count = 0;

	while (current != NULL)
	{
		count = count + 1;
		current = current->next;
	}

	return (count);
}
