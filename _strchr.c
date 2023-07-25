#include <stdio.h>

/**
* _strchr - checks for a character within a string
* @str: string
* @c: character to find
* Return: str if character is found
* NULL if character is not found
*/
char *_strchr(char *str, int c)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			return (str);
		}
		i++;
	}
	return (NULL);
}
