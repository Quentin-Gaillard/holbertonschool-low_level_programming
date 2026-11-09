#include "main.h"
#include <stdlib.h>

/**
 * alloc_grid - Alloue une grille à 2 dimensions d'entiers initialisés à 0.
 * @width: Largeur de la grille (nombre de colonnes).
 * @height: Hauteur de la grille (nombre de lignes).
 *
 * Return: Un pointeur vers la grille allouée (int **),
 *         ou NULL en cas d'échec ou si width/height <= 0.
 */
int **alloc_grid(int width, int height)
{
	int **grid;
	int **row_ptr;
	int *col_ptr;
	int h, w;

	if (width <= 0 || height <= 0)
		return (NULL);

	grid = malloc(height * sizeof(int *));
	if (grid == NULL)
		return(NULL);

	row_ptr = grid;
	for (h = 0; h < height; h++)
	{
		*row_ptr = malloc(width * sizeof(int));
		if (*row_ptr == NULL)
		{
			while (row_ptr != grid)
			{
				row_ptr--;
				free(*row_ptr);
			}
			free(grid);
			return(NULL);
		}
		row_ptr++;
	}
	row_ptr = grid;
	for (h= 0; h < height; h++)
	{
		col_ptr = *row_ptr;
		for (w = 0; w < width; w++)
		{
			*col_ptr = 0;
			col_ptr++;
		}
		row_ptr++;
	}

	return(grid);
}
