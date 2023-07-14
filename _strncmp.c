#include <stdio.h>
/**
 * _strncmp - compare two string characters based on the length given
 * @s1: first string.
 * @s2: second string.
 * @len: length of string to compare.
 *
 * Return: 0 if the two string are the same.
 * 1 if they are not the same.
 * -1 error
 */
int _strncmp(char *s1, char *s2, int len)
{
	int i;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	for (i = 0; i < len; i++)
	{
		if (s1[i] != s2[i])
		{
			return (1);
		}
	}
	return (0);
}
