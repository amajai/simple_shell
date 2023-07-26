#include <stdio.h>
#include "main.h"

/**
 * check_value - checks if pname passed is an alias to get its value. if not,
 * it returns the pname.
 * @pname: command line first argument
 * @aliases: array of aliases
 *
 * Return: value, from struct if its an alias
 * pname of not an alias
 */
char *check_value(char *pname, alias_t **aliases)
{
	int i = 0;

	if (aliases != NULL)
	{
		while (aliases[i] != NULL)
		{
			if (_strcmp(pname, aliases[i]->name) == 0)
			{
				return (check_value(aliases[i]->value, aliases));
			}
			i++;
		}
	}
	return (_strdup(pname));
}
