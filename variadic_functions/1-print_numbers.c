#include <stdio.h>
#include <stdarg.h>
#include "variadic_functions.h"

/**
 * print_numbers - affiche des nombres suivis d'un retour a la ligne
 * @separator: chaine de caracteres a afficher entre les nombres
 * @n: nombre d'entiers passes a la fonction
 */

void print_numbers(const char *separator, const unsigned int n, ...)
{
	va_list liste_args;
	unsigned int i;
	int nombre;

	/* On démarre la foction juste apres le parametre n */
	va_start(liste_args, n);

	for (i = 0; i < n; i++)
	{
		/* On attrape le nombre suivant et on l'affiche */
		nombre = va_arg(liste_args, int);
		printf("%d", nombre);

		/* On affiche le separateur s'il existe et si ce n'est pas le dernier */
		if (separator != NULL && i < n - 1)
		{
			printf("%s", separator);
		}
	}
	/* On ferme la fonction roulant et on saute une ligne a la fin */
	va_end(liste_args);
	printf("\n");
}
