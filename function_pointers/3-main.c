#include <stdio.h>
#include <stdlib.h>
#include "3-calc.h"

/**
 * main - Effectue des operations arithmetique simples via la ligne de commande
 * @argc: Nombre d'arguments passes au programme
 * @argv: Tableau de chaines contenant les arguments
 *
 * Return: Toujours 0 en cas de succes.
 */
int main(int argc, char *argv[])
{
	int num1, num2;
	int (*func)(int, int);

	/* 1. Verifie que l'utilisateur a bien donne exactement 3 arguments */
	if (argc != 4)
	{
		printf("Error\n");
		exit(98);
	}

	/* 2. Recupere le pointeur de fonction correspondant a l'operateur */
	func = get_op_func(argv[2]);
	if (func == NULL)
	{
		printf("Error\n");
		exit(99);
	}

	/* Convertit les deux nombres textes en vrais entiers */
	num1 = atoi(argv[1]);
	num2 = atoi(argv[3]);

	/* 3. Empeche la division ou le modulo par zero */
	if ((argv[2][0] == '/' || argv[2][0] == '%') && num2 == 0)
	{
		printf("Error\n");
		exit(100);
	}

	/* Execute la fonction pointee et affiche le resultat */
	printf("%d\n", func(num1, num2));
	return (0);
}
