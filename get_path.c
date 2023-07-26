#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "main.h"

/**
* get_path - checks if pname input is a valid program and creates valid path.
* @pname: program name
* @buf: command line input buffer
* Return: path if success
* NULL if pname is not a valid program path
*/
char *get_path(char *pname, char *buf)
{
	char *token, *new_path, *paths;
	unsigned int token_len, pname_len;
	struct stat st;

	paths = malloc(sizeof(char) * (_strlen(_getenv("PATH")) + 1));
	if (paths == NULL)
		return (NULL);
	_strcpy(paths, _getenv("PATH"));
	token = strtok(paths, ":");
	while (token != NULL)
	{
		token_len = _strlen(token);
		pname_len = _strlen(pname);
		new_path = malloc(sizeof(char) * (token_len + pname_len + 2));
		if (new_path == NULL)
			return (NULL);
		joinpath(new_path, token, token_len, pname, pname_len);
		if (stat(new_path, &st) == 0)
		{
			free(paths);
			free(pname);
			free(buf);
			return (new_path);
		}
		free(new_path);
		token = strtok(NULL, ":");
	}
	free(paths);
	return (NULL);
}
