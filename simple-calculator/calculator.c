#include <stdio.h>

/**
 * print_menu - Affiche les choix possibles demandés par l'exercice.
 * PREMIERE FONCTION
 * Return: Nothing (void)
 */
void print_menu(void)
{
	/*Affiche les 5 choix possibles + le choix de l'utilisateur */
	printf("1) Add\n");
	printf("2) Substract\n");
	printf("3) Multiply\n");
	printf("4) Divide\n");
	printf("0) Quit\n");
	printf("Choice: ");
}

/**
 * main - Ici, première intéraction avec l'utilisateur
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	/*
	 * Déclare et initialise la variable pour le menu de sélection
	 * -1 pour pour que le programme se lance et éviter une boucle
	 * infinie et pas 1,2,3,4 pour que le code soit lisible
	 */
	int choice = -1;

	/*Affiche la banière Simple Calculator */
	printf("Welcome to my first Simple calculator\n");

	/*Ici, PREMIERE intéraction avec l'utilisateur */
	while (choice != 0)
	{
		print_menu();
		/* PREMIER scanf, lire le choix de l'utlisateur*/
		if (scanf("%d", &choice) != 1)
			break;

		if (choice == 0)
			printf("Bye, Have a nice day\n");
	}

	return (0);
}
