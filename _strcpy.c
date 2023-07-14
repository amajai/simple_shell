#include <stdio.h>
/**
 * _strcpy - copy characters from one string to another.
 * @copy: empty array to copy to.
 * @origin: array to copy from.
 *
 * Return: copied array.
 * NULL if copy is NULL.
 */
char *_strcpy(char *copy, char *origin)
{
	int i = 0;

	if (copy == NULL)
		return (NULL);

	while (origin[i] != '\0')
	{
		copy[i] = origin[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
