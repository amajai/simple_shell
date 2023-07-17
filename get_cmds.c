#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

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
	int i = 0, j = 0, cmd_count = 0, start = 0, end = _strlen(buffer) - 1;

	while (buffer[start] == ' ' || buffer[start] == '\t')
		start++;

	while (end > start && buffer[end] == ' ')
		end--;

	for (i = 0; start <= end; i++, start++)
	{
		buffer[i] = buffer[start];
	}

	buffer[i] = '\0';

	i = 0;
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
