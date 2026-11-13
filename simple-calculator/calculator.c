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
 * TACHE 2.
 * add - Additionne deux nombres
 * @a: Premier nombre
 * @b: Deuxième nombre
 *
 * Return: résultat de la somme des deux nombres
 */
double add(double a, double b)
{
	return (a + b);
}
/**
 * TACHE 3.
 * substract - Soustrait deux nombres
 * @a: Premier nombre
 * @b: Deuxième nombre
 *
 * Return: résultat de la soustraction des deux nombres
 */
double substract(double a, double b)
{
	return (a - b);
}
/**
 * TACHE 4.
 * multiply - Multiplie deux nombres
 * @a: Premier nombre
 * @b: Deuxième nombre
 *
 * Return: résultat de la multiplcation des deux nombres
 */
double multiply(double a, double b)
{
	return (a * b);
}



double divide(double a, double b)
{
	return (a / b);
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
	/* TACHE 2, ajout a, b, result pour l'addition,
	 *TACHE 3, on ajoute = 0,
	 */
	double a, b, result = 0;

	/*TACHE 0 : Affiche la banière Simple Calculator */
	printf("Welcome to my first Simple calculator, tas d'apprenants' \n");

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
		/* TACHE 2 a partir d'ici avec comme choix 1 */
		else
		{
			/*
			 * %lf = long float pour lire un double
			 * %g = supprime les zero inutiles après la virgule.
			 * divisions avec décimales
			 */

				printf("A: ");
			if (scanf("%lf", &a) != 1)
				break;
			printf("B: ");
			if (scanf("%lf", &b) != 1)
				break;

			if (choice == 1)
			{
				result = add(a, b);
				printf("Result: %g\n", result);
			}
			else if (choice == 2)
			{
				result = substract(a, b);
				printf("Result: %g\n", result);
			}
			else if (choice == 3)
			{
				result = multiply(a, b);
				printf("Result: %g\n", result);
			}
			else if (choice == 4)
			{
				if (b == 0)
					printf("ERROR: division by zero\n");
				else
				{
					result = divide(a, b);
					printf("Result: %g\n", result);
				}
			}

		}
	}

	return (0);
}
