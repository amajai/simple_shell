#include <stddef.h>
#include "main.h"

/**
 * trim - remove spaces and newline from start and end of a string
 * @str: string
 * Return: Nothing
 */
void trim(char **str)
{
	int i = 0, start = 0, end = _strlen((*str)) - 1;

	while ((*str)[start] == ' ' || (*str)[start] == '\t')
		start++;

	while ((end > start && (*str)[end] == ' ') || (*str)[end] == '\n')
		end--;

	for (i = 0; start <= end; i++, start++)
	{
		(*str)[i] = (*str)[start];
	}

	(*str)[i] = '\0';
}
