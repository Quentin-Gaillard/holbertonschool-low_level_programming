#include "main.h"

/**
 * print_alphabet_x10 - Prints the alphabet 10 times in lowercase
 *
 * Description: Uses nested loops to print the lowercase alphabet
 * ten times, each time followed by a newline character.
 */
void print_alphabet_x10(void)
{
	int i;
	char c;

	for (i = 0; i < 10; i++)
	{
		for (c = 'a'; c <= 'z'; c++)
		{
			_putchar(c); /* Premier _putchar pour les lettres */
		}
		_putchar('\n'); /* Second _putchar pour le retour à la ligne */
	}
}
