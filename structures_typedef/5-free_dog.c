#include <stdlib.h>
#include "dog.h"

/**
 * free_dog - libérez les mémoires allouées a struct dog
 * @d: pointeur vers la mémoire a libérer
 */

void free_dog(dog_t *d)
{
	if (d != NULL)
	{
		free(d->name);
		free(d->owner);
		free(d);
	}
}
