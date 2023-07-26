#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"

/**
* print_env - prints the environment variables
* @env: list of environment variables
*
* Return: Nothing
*/
int print_env(char **env)
{
	int i;

	if (env == NULL)
		exit(1);
	else
	{
		for (i = 0; env[i] != NULL; i++)
		{
			write(1, env[i], _strlen(env[i]));
			_putchar('\n');
		}
	}
	return (0);
}
