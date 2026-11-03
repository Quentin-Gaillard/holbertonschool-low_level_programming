#include "main.h"

/**
 * _strlen - Returns the length of a string.
 * @s: A pointer to a string (array of characters).
 * Juste pour calculer la longueur de la chaîne de caractères.
 * Return: The length of the string as an integer.
 */
int _strlen(char *s)
{
	int count;

	count = 0;
	while (s[count] != '\0')
	{
		count++;
	}

	return (count);
}
