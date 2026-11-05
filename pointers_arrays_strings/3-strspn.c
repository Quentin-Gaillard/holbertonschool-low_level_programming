#include "main.h"

/**
 * _strspn - Gets the length of a prefix substring.
 * @s: 1ere list de carctères
 * @accept: liste qui xontient les caractèrents voulus
 *
 * Return: The number of bytes in the initial segment of s
 *         which consist only of bytes from accept.
 */
unsigned int _strspn(char *s, char *accept)
{
	unsigned int count = 0;
	char *p;

	while (*s != '\0')
	{
		for (p = accept; *p != '\0'; p++)
		{
			if (*s == *p)
			{
				break;
			}
		}

		if (*p == '\0')
		{
			return (count);
		}

		count++;
		s++;
	}

	return (count);
}
