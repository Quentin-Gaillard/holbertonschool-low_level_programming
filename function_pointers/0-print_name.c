#include "function_pointers.h"

/**
 * print_name - affiche un nom utilisant la fonction donnée
 * @name: chaine contenant le nom a afficher
 * @f: pointeur montrant la fonctuion a utiliser
 *
 * Return: Nothing.
 */

void print_name(char *name, void (*f)(char *))
{
	if (name == NULL || f == NULL)
		return;

	(*f)(name);
}
