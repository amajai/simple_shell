#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * get_cmds - Get all commands seperated by semi-colon if present and add them
 * to an array ending with NULL
 * @buffer: command line input buffer.
 *
 * Return: array of commands ending with NULL.
 */
char **get_cmds(char *buffer)
{
	char *token, **arr;
	int i = 0, j = 0, cmd_count = 0;

	while (buffer[i] != '\0')
	{
		if (buffer[i] == ';')
			cmd_count++;
		i++;
	}
	cmd_count++;
	arr = malloc(sizeof(char *) * (cmd_count + 1));
	token = strtok(buffer, ";\n");
	while (token != NULL)
	{
		(arr)[j] = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy((arr)[j++], token);
		token = strtok(NULL, ";\n");
	}
	(arr)[j] = NULL;
	return (arr);
}
