#include <unistd.h>

/**
 * _strlen - counts number of characters in a string excluding the
 * null terminating character.
 * @str: The string.
 *
 * Return: length of string.
 */
unsigned int _strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;

	return (i);
}
