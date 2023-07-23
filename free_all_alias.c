#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
* free_all_alias - free all the allocated memory of a struct
* @aliases: array of aliases
*
* Return: Nothing
*/
void free_all_alias(struct alias **aliases)
{
	int i = 0;

	while (aliases[i] != NULL)
	{
		free(aliases[i]->name);
		free(aliases[i]->value);
		free(aliases[i]);
		i++;
	}
	free(aliases);
}
