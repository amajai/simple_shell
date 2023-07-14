#include <stdio.h>

/**
 * joinpath - combine a string with another string to create new path.
 * @dest: empty array string to contain new path.
 * @s1: first string. Will added first.
 * @s1_len: length of first string.
 * @s2: second string. Will be added after the first string.
 * @s2_len: length of second string.
 *
 * Return: combined new string path.
 */
char *joinpath(char *dest, char *s1, size_t s1_len, char *s2, size_t s2_len)
{
	unsigned int i, j;

	for (i = 0; i < s1_len; i++)
		dest[i] = s1[i];
	dest[i++] = '/';
	for (j = 0; j < s2_len; j++)
		dest[i++] = s2[j];
	dest[i] = '\0';
	return (dest);
}
