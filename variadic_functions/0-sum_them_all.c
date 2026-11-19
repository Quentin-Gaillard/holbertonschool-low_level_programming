#include <stdarg.h>
#include "variadic_functions.h"

/**
 * sum_them_all - retourne la somme de tous ses parametres
 * @n: nombre de parametres passes a la fonction
 *
 * Return: la somme des parametres, ou 0 si n est egal a 0
 */

int sum_them_all(const unsigned int n, ...)
{
	va_list liste_args;
	unsigned int i;
	int somme;
	int nombre;

	/* Si aucun parametre n'est donné, on renvoie 0 tout de suite */
	if (n == 0)
	{
		return (0);
	}

	/* On met la somme a zero et on place le "compteur" après n */
	somme = 0;
	va_start(liste_args, n);

	/* On fait n tours pour attraper chaque nombre et l'additionner */
	for (i = 0; i < n; i++)
	{
		nombre = va_arg(liste_args, int);
		somme = somme + nombre;
	}

	/* On ferme proprement le"compteur et on renvoie le total */
	va_end(liste_args);

	return (somme);
}
