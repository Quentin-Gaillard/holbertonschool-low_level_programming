#include "main.h"
#include <stdlib.h>

/**
 * str_concat - Concatène deux chaînes sans utiliser i et j.
 * @s1: La première chaîne.
 * @s2: La deuxième chaîne.
 *
 * Return: Un pointeur vers le nouvel espace alloué, ou NULL si échec.
 */

char *str_concat(char *s1, char *s2)
{
	char *concat;
	char *dest;
	unsigned int l1 = 0;
	unsigned int l2 = 0;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";

	while (s1[l1] != '\0')
		l1++;

	while (s2[l2] != '\0')
		l2++;

	concat = malloc((l1 + l2 + 1) * sizeof(char));

	if (concat == NULL)
		return (NULL);

	dest = concat;

	while (*s1 != '\0')
	{
		*dest = *s1;
		dest++;
		s1++;
	}

	while (*s2 != '\0')
	{
		*dest = *s2;
		dest++;
		s2++;
	}

	*dest = '\0';

	return (concat);
}
