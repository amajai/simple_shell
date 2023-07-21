#include <stdio.h>

/**
 * _atoi - converts a string to an interger
 * @s: string to convert
 * Return: s, if no any number Return 0
 */

int _atoi(char *s)
{
	int i, minus = 0;
	unsigned int num;

	i = 0;
	num = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '-')
			++minus;
		if (s[i] >= '0' && s[i] <= '9')
		{
			num = num * 10 + ((s[i]) - '0');
			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
		}
		i++;
	}

	if (num)
	{
		if (minus % 2)
			return (-num);
		else
			return (num);
	}

	return (0);
}
