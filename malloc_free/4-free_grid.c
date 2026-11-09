#include "main.h"
#include <stdlib.h>

/**
 * free_grid - Libère la mémoire d'une grille à 2 dimensions.
 * @grid: Pointeur vers la grille d'entiers (int **).
 * @height: Hauteur de la grille (nombre de lignes).
 *
 * Return: Rien (void).
 */
void free_grid(int **grid, int height)
{
	int **row_ptr;
	int h;

	if (grid == NULL || height <= 0)
	{
		return;
	}

	row_ptr = grid;
	for (h = 0; h < height; h++)
	{
		free(*row_ptr);
		row_ptr++;
	}

	free(grid);
}
