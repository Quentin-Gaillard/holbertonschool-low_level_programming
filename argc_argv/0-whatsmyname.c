#include <stdio.h>

/**
 * main - affiche le nom du programme suivi d'un retour a la ligne
 * @argc: nombre d'arguments DE LA ligne de commande du terminal
 * @argv: tableau d'arguments DE LA ligne de commande
 *
 * Return: Always 0 (Success)
 */

int main(int argc, char *argv[])
{
	/**
	 * ici (void)argc; indique au compilateur qu'on SAIT que cette variable
	 * existe MAIS que je ne m'en sers pas
	 */
	(void)argc;

	printf("%s\n", argv[0]);

	return (0);
}
