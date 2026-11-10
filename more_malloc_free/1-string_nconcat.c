#include "main.h"
#include <stdlib.h>

/**
 * string_nconcat - Concatène deux chaînes avec une limite n sur s2.
 * @s1: La première chaîne.
 * @s2: La deuxième chaîne.
 * @n: Le nombre maximal d'octets à copier de s2.
 *
 * Return: Un pointeur vers le nouvel espace alloué, ou NULL si échec.
 */

char *string_nconcat(char *s1, char *s2, unsigned int n)
{
	char *str;
	char *dest;
	unsigned int len1 = 0;
	unsigned int len2 = 0;
	unsigned i;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";

	dest = s1;
	while (*dest != '\0')
	{
		len1++;
		dest++;
	}
	dest = s2;
	while (*dest != '\0')
	{
		len2++;
		dest++;
	}
	if (n >= len2)
		n = len2;
	str = malloc((len1 + n + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	dest = str;
	while (*s1 != '\0')
	{
		*dest = *s1;
		dest++;
		s1++;
	}
	for (i = 0; i < n; i++)
	{
		*dest = *s2;
		dest++;
		s2++;
	}
	*dest = '\0';
	return (str);
}
