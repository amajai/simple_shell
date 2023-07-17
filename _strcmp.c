/**
 * _strcmp - compares two strings
 * @s1: String one
 * @s2: String two
 * Return: 0 when str are same else the difference
 */

int _strcmp(char *s1, char *s2)
{
	int i, diff = 0;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			diff = s1[i] - s2[i];
			break;
		}
		i++;
	}

	return (diff);
}
