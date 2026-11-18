#include <stdio.h>

/**
 * main - affiche tous les arguments qu'il recoit
 * @argc: nombre d'arguments de la ligne de commande
 * @argv: tableau du nombre d'arguments de la ligne de commande
 *
 * Return: Always 0 (Success)
 */

int main(int argc, char *argv[])
{
	int i;

	for (i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}
	return (0);
}
