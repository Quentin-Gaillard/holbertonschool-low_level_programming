#include <stdio.h>
#include <stdarg.h>
#include "variadic_functions.h"

/**
 * print_strings - affiche des chaines suivies d'un retour a la ligne
 * @separator: chaine de caracteres a afficher entre les chaines
 * @n: nombre de chaines passees a la fonction
 */

void print_strings(const char *separator, const unsigned int n, ...)
{
	va_list liste_args;
	unsigned int i;
	char *texte;

	/* PLacement fonction juste apres parametre n */
	va_start(liste_args, n);

	/* On parcourt les n strings une par une */
	for (i=0; i < n; i++)
	{
		/* 1. On attrape la chaine suivante sur le tapis roulant */
		texte = va_arg(liste_args, char *);
		/* 2. On verifie si la chaine est NULL ou valide */
		if (texte == NULL)
		{
			printf("(nil)");
		}
		else
		{
			printf("%s", texte);
		}
		/* 3. On verifie si on est AVANT la derniere chaine */
		if (i < n - 1)
		{
			/* 4. On verifie si le separateur existe */
			if (separator != NULL)
			{
				printf("%s", separator);
			}
		}
	}
	/* On ferme le tapis roulant et on saute une ligne a la fin */
	va_end(liste_args);
	printf("n");
}
