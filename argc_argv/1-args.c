#include <stdio.h>

/**
 * main - Affiche le nombre d'arguments sans celui du programme ./nargs)
 * @argc: nombre d'arguments de la ligne de commande
 * @argv: tableau du nombre d'arguments de la ligne de commande
 *
 * Return: Always 0 (Success)
 */

int main(int argc, char *argv[])
{
	/** ici (void)argc; indique au compilateur quon SAIT que cette variable
	 * existe MAIS que je ne m'en sers pas, avec argc -1 pour faire sauter
	 * le premier argument argv[0] ./nargs
	 */

	(void)argv;

	printf("%d\n", argc - 1);

	return (0);
}
