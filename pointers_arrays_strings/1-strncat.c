#include "main.h"

/**
 *_strncat - Concatène deux 'strings' en usant au plus n octets de src
 * @dest: La chaine de destination à laquelle le texte sera ajouét
 * @src: Le chaine source à ajouter
 * @n: Le nombre maxi d'octets à copier depuis src
 *
 * Return: Un pointeur vers la chaine finale dest.
 */

char *_strncat(char *dest, char *src, int n)
{
	int i = 0;
	int j = 0;

	while (dest[i] != '\0')
	{
		i++;
	}

	while (j < n && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';

	return (dest);
}
