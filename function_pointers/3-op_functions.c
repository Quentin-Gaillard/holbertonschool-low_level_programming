#include "3-calc.h"

/**
 * op_add - Calcule la somme de deux entiers
 * @a: Premier entier
 * @b: Deuxieme entier
 *
 * Return: La somme (selon le type) de a et b.
 */
int op_add(int a, int b)
{
	/* Additionne a et b et renvoie le resultat */
	return (a + b);
}

int op_sub(int a, int b)
{
	/* Soustrait b de a et renvoie le resultat */
	return (a - b);
}

int op_mul(int a, int b)
{
	/* Multiplie a par b et renvoie le resultat */
	return (a * b);
}

int op_div(int a, int b)
{
	/* Divise a par b et renvoie le quotient entier */
	return (a / b);
}

int op_mod(int a, int b)
{
	/* Calcule le modulo de a par b et renvoie le reste */
	return (a % b);
}
