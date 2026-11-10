#include "main.h"
#include <stdlib.h>


/**
 * array_range - Crée un tableau d'entiers contenant une plage de valeurs.
 * @min: La valeur minimale (incluse).
 * @max: La valeur maximale (incluse).
 *
 * Return: Un pointeur vers le tableau alloué, ou NULL si min > max ou échec.
 */

int *array_range(int min, int max)
{
	int *tableau;
	int *remplisseur;
	int i;

	if (min > max)
		return (NULL);

	tableau = malloc ((max - min + 1) * sizeof (int));
	if (tableau == NULL)
		return (NULL);

	remplisseur = tableau;
	for (i = min; i <= max; i++)
		*remplisseur++ = i;

	return (tableau);
}
