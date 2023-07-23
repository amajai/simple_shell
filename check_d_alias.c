/**
 * check_d_alias - check if the string is an alias variable assignment format
 * x=y or a='b' or y="z"
 * @str:string
 *
 * Return: 0 if true
 * 1 if false
 */
int check_d_alias(char *str)
{
	int i = 0, lv = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '=' && i > 0 && lv > 0)
			return (0);
		else if (str[i] == ' ')
			return (1);
		i++;
		lv++;
	}
	return (1);
}
