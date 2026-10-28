#include "main.h"

/**
 * print_alphabet - Prints the alphabet in lowercase
 *
 * Description: Loops through characters from a to z and prints them,
 * followed by a new line. Uses _putchar exactly twice.
 */
void print_alphabet(void)
{
	char letter;

	for (letter = 'a'; letter <= 'z'; letter++)
	{
		_putchar(letter);
	}
	_putchar('\n');
}
