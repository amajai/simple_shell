#include <stdio.h>
#include <stdlib.h>

/**
 * _realloc - reallocates a memory block using malloc and free.
 * @ptr: pointer to memory previously allocated.
 * @old_size: size of previous memory.
 * @new_size: size of new memory.
 *
 * Return: pointer to memory for new array, else NULL if it fails.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *mem;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	mem = malloc(new_size);
	if (mem == NULL)
		return (NULL);

	if (ptr == NULL)
		return (mem);

	for (i = 0; i < old_size; i++)
		((char *) mem)[i] = ((char *) ptr)[i];

	free(ptr);
	return (mem);
}
