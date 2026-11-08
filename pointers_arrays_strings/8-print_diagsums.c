#include "main.h"
#include <stdio.h>

/**
 * print_diagsums - Affiche la somme des deux diagonales d'une matrice carrée
 * @a: Pointeur vers le premier élément de la matrice.
 * @size: Taille de la matrice (largeur/hauteur)
 *
 * Return: void
 */
void print_diagsums(int *a, int size)
{
	int i;
	int sumdiag1 = 0;
	int sumdiag2 = 0;

	for (i = 0; i < size; i++)
	{
		sumdiag1 += a[(i * size) + i];
		sumdiag2 += a[(i * size) + (size - 1 - i)];
	}

	printf("%d, %d\n", sumdiag1, sumdiag2);
}
