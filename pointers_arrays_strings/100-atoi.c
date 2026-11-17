#include "main.h"

/**
 * _atoi - Convertit une chaine de caracteres en entier
 * @s: Chaine de caracteres a convertir
 *
 * Return: L'entier extrait de la chaine, ou 0 s'il n'y a aucun chiffre.
 */
int _atoi(char *s)
{
	int i;
	int sign;
	unsigned int res;

	i = 0;
	sign = 1;
	res = 0;

	/* Parcourt la chaine tant qu'on n'a pas atteint la fin */
	while (s[i] != '\0')
	{
		/* Inverse le signe a chaque '-' croise avant le nombre */
		if (s[i] == '-')
			sign *= -1;

		/* Des qu'on croise le premier chiffre, on lit tout le nombre */
		if (s[i] >= '0' && s[i] <= '9')
		{
			while (s[i] >= '0' && s[i] <= '9')
			{
				res = (res * 10) + (s[i] - '0');
				i++;
			}
			/* Stoppe immediatement apres la fin du premier nombre */
			break;
		}
		i++;
	}

	return (res * sign);
}
