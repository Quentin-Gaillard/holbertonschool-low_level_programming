#include <stdio.h>
#include <stdarg.h>
#include "variadic_functions.h"

/**
 * print_all - affiche n'importe quel type d'argument qui passe en paramètre
 * @format: liste des types d'arguments passés a la fonction
 */

void print_all(const char * const format, ...)
{
	va_list liste_args;
	int i;
	char *separateur;
	char lettre;
	int entier;
	double decimal;
	char *texte;

	/* On met l'index a 0, le séparateur vide et on lance la fonction */
	i = 0;
	separateur = "";
	va_start(liste_args, format);

	/* 1er if : on vérifie que format n'est pas NULL */
	if (format != NULL)
	{
		/* 1ère boucle while : on lit format lettre par lettre */
		while (format[i] != '\0')
		{
			/* On aiguille selon la lettre lue dans format */
			switch (format[i])
			{
				/* Cas 'c':on attrape et afiche un caractere */
				case 'c':
					lettre = va_arg(liste_args, int);
					printf("%s%c", separateur, lettre);
					separateur = ", ";
					break;
				/* Cas 'i' :  un nombre entier */
				case 'i':
					entier = va_arg(liste_args, int);
					printf("%s%d", separateur, entier);
					separateur = ", ";
					break;
				/* Cas 'f' : un nombre a virgule */
				case 'f':
					decimal = va_arg(liste_args, double);
					printf("%s%f", separateur, decimal);
					separateur = ", ";
					break;
				/* Cas 's' : une chaine de texte */
				case 's':
					texte = va_arg(liste_args, char *);
					/* 2eme if  : si le texte est vide */
					if (texte == NULL)
					{
						texte = "(nil)";
					}
					printf("%s%s", separateur, texte);
					separateur = ", ";
					break;
			}
			/* On passe a la lettre suivante dans format */
			i++;
		}
	}

	/* On ferme lafonction et on saute une ligne a la fin */
	va_end(liste_args);
	printf("\n");

}
