#include "main.h"

/**
 * cap_string - Mets en majuscules toutes les 1 ères lettres des mots.
 * @str: pointeur a la phrase a modifier.
 *
 * Return: pointer à la phrase modifiée.
 */
char *cap_string(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		/* Si c'est une minuscule */
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			/* Si c'est le tout premier caractère du texte */
			if (i == 0)
			{
				str[i] -= 32;
			}
			/* OU si le caractère juste avant fait partie des séparateurs */
			else if (str[i - 1] == ' ' || str[i - 1] == '\t' ||
				 str[i - 1] == '\n' || str[i - 1] == ',' ||
				 str[i - 1] == ';' || str[i - 1] == '.' ||
				 str[i - 1] == '!' || str[i - 1] == '?' ||
				 str[i - 1] == '"' || str[i - 1] == '(' ||
				 str[i - 1] == ')' || str[i - 1] == '{' ||
				 str[i - 1] == '}')
			{
				str[i] -= 32;
			}
		}
		i++;
	}

	return (str);
}
