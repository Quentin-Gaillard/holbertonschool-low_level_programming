#include "main.h"
#include <stdlib.h>

/**
 * _strdup - Renvoie un pointeur vers un nouvel espace mémoire alloué,
 *           qui contient une copie de la chaîne passée en paramètre.
 * @str: La chaîne de caractères à dupliquer.
 *
 * Return: Un pointeur vers la chaîne dupliquée,
 *         ou NULL si str vaut NULL ou si la mémoire est insuffisante.
 */

char *_strdup(char *str)
{
	char *copy;
	unsigned int i;
	unsigned int len;

	if (str == NULL)
	{
		return (NULL);
	}

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}

	copy = malloc ((len +1) * sizeof(char));

	if (copy == NULL)
	{
		return (NULL);
	}

	i = 0;
	while (i <= len)
	{
		copy[i] = str[i];
		i++;
	}
	return (copy);
}
