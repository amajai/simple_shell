#include<stdlib.h>
#include "main.h"

/**
 * _strdup - copy the string input.
 * @str: the string
 *
 * Return: duplicate of the input string.
 */
char *_strdup(const char *str)
{
	size_t i;
	size_t len;
	char *str_cpy;

	len = _strlen(str) + 1; /* with null terminator */
	str_cpy = malloc(sizeof(char) * len);

	if (str_cpy == NULL)
		return (NULL);

	for (i = 0; i < len - 1; i++)
	{
		str_cpy[i] = str[i];
	}
	str_cpy[i] = '\0';
	return (str_cpy);
}
