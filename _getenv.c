#include <stdio.h>
#include "main.h"
/**
* _getenv - finds key name within an env array
* @name: variable name to be searched for
*
* Return: token if successful
*/

char *_getenv(char *name)
{
	int i;
	char *envpath = NULL;
	int name_len;

	name_len = _strlen(name);
	for (i = 0; environ[i] != NULL; ++i)
	{
		if (_strncmp(environ[i], name, name_len) == 0)
		{
			if (environ[i][name_len] == '=')
			{
				envpath = environ[i] + name_len;
				break;
			}
		}
	}
	return (envpath);
}
