#include "3-calc.h"

/**
 * get_op_func - Selectionne la bonne fonction pour effectuer l'operation
 * @s: Chaine de caracteres representant l'operateur passe en argument
 *
 * Return: Pointeur vers la fonction correspondante, ou NULL si introuvable.
 */
int (*get_op_func(char *s))(int, int)
{
	/* Tableau associatif liant chaque symbole a sa fonction */
	op_t ops[] = {
		{"+", op_add},
		{"-", op_sub},
		{"*", op_mul},
		{"/", op_div},
		{"%", op_mod},
		{NULL, NULL}
	};
	int i;

	i = 0;
	/* Parcourt le tableau jusqu'a atteindre la sentinelle NULL */
	while (ops[i].op != NULL)
	{
		/* Verifie que s existe, fait 1 caractere et egale ops[i].op */
		if (s != NULL && s[0] == ops[i].op[0] && s[1] == '\0')
			return (ops[i].f);
		i++;
	}

	/* Aucun operateur valide n'a ete trouver */
	return (NULL);
}
