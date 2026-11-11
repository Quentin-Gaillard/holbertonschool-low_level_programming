#include <stdio.h>

/**
 * print_menu - Affiche les choix possibles demandés par l'exercice.
 * TACHE 0 : PREMIERE FONCTION
 * Return: Nothing (void)
 */
void print_menu(void)
{
	/*TACHE 0 Affiche les 5 choix possibles + le choix de l'utilisateur */
	printf("1) Add\n");
	printf("2) Substract\n");
	printf("3) Multiply\n");
	printf("4) Divide\n");
	printf("0) Quit\n");
	printf("Choice: ");
}

/**
 * main - Ici, première intéraction avec l'utilisateur
 * TACHE 0
 * Return: Always 0 (Success)
 */
int main(void)
{
	/*
	 * TACHE 0:Déclare et initialise la variable pour le menu de sélection
	 * -1 pour pour que le programme se lance et éviter une boucle
	 * infinie et pas 1,2,3,4 pour que le code soit lisible
	 */
	int choice = -1;

	/*TACHE 0 : Affiche la banière Simple Calculator */
	printf("Welcome to my first Simple calculator\n");

	/*TACHE 0 Ici, PREMIERE intéraction avec l'utilisateur */
	while (choice != 0)
	{
		print_menu();
		/*
		 * TACHE 0 :PREMIER scanf, lire le choix de l'utlisateur
		 * avec &qiu donne l'adresse mémoire de choice pour que
		 * l'utilisateur puisse la déposer
		 */
		if (scanf("%d", &choice) != 1)
			break;

		if (choice == 0)
			printf("Bye, Have a nice day\n");
		/*
		 * TACHE 1, ici on ajoute le vigile qui saque si on affiche
		 * en dessous de zéro OU au dessus de 4
		 */
		else if (choice < 0 || choice > 4)
		{
			printf("Invalid choice\n");
		}
	}

	return (0);
}
