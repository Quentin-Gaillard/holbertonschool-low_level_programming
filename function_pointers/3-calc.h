#ifndef CALC_H
#define CALC_H

#include <stddef.h>

/**
 * struct op - Structure associan un opérateur a sa fonction de calcul
 *
 * @op: Chaine de caracteres representant l'operateur (+, -, *, /, %)
 * @f: Pointeur vers la fonction mathematique associee
 */

typedef struct op
{
	/* Compartiment 1 : stocke le symbole de l'operateur */
	char *op;
	/* Compartiment 2 : stocke l'adresse de la fonction de calcul */
	int (*f)(int a, int b);
} op_t;

/* Prototypes des 5 fonctions mathematiques pour le 3-op_functions.c */
int op_add(int a, int b);
int op_sub(int a, int b);
int op_mul(int a, int b);
int op_div(int a, int b);
int op_mod(int a, int b);
/* Prototype de la fonction de selection d'operateur pour le 3-get_op_func.c */
int (*get_op_func(char *s))(int, int);

#endif
