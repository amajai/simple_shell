/**
 * _isdigit - Checks if string contains numbers
 * @str: string to inspect
 * Return: 1 if true 0 false
 */

int _isdigit(char *str)
{
	int len = 0;
	int i = 0;

	while (str[len])
		len++;

	if (str[i] == '-') /* If number is negative */
		i++;

	while (str[i])
	{
		if (str[i] == '-')
			continue;
		if (str[i] <= '0' || str[i] >= '9')
			break;
		i++;
	}

	if (len == i)
		return (1);
	else
		return (0);
}
