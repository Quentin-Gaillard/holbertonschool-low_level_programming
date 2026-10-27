#include <stdio.h>

/**
 * main - Entry point of the program
 *
 * Description: Prints the alphabet in lowercase, and then in uppercase,
 * followed by a new line.
 * Return: Always 0 (Success)
 */
int main(void)
{
	char ch;

	/* Loop for lowercase */
	for (ch = 'a'; ch <= 'z'; ch++)
	{
		putchar(ch);
	}

	/* Loop for uppercase */
	for (ch = 'A'; ch <= 'Z'; ch++)
	{
		putchar(ch);
	}

	/* Retour à la ligne final */
	putchar('\n');

	return (0);
}
