#include "main.h"

/**
 * string_toupper - change les lettres minuscules en majuscules
 * @str: montre la phrase a midifier
 *
 * Return: pointe la phrase modifiée
 */
char *string_toupper(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] = str[i] - 32;
		}
		i++;
	}

	return (str);
}
