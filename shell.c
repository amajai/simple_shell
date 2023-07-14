#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "main.h"

/**
 * main - A UNIX command line interpreter.
 * @ac: number of arguements
 * @av: arguements entered
 * @env: bash enviroments
 * Return: 0
 */

int main(int ac, char **av, char **env)
{
	size_t n = 0;
	pid_t pid;
	char *buffer = NULL, **cmds = NULL, *token, *dupbuff;
	int cmd, status;

	(void)ac;
	isatty(STDIN_FILENO) ? write(1, "$ ", 2) : write(1, "", 0);
	while ((cmd = getline(&buffer, &n, stdin)) != EOF)
	{
		cmds = malloc(sizeof(char *) * 2);
		dupbuff = _strdup(buffer);
		token = strtok(dupbuff, "\n");
		cmds[0] = token;
		cmds[1] = NULL;
		pid = fork();
		if (pid == -1)
		{
			perror("Error:");
			return (1);
		}
		else if (pid == 0)
		{
			if (execve(cmds[0], cmds, env) == EOF)
			{
				perror(av[0]);
				free(dupbuff);
				free(cmds);
				free(buffer);
				return (1);
			}
		}
		else
			wait(&status);
		free(cmds);
		free(dupbuff);
		isatty(STDIN_FILENO) ? write(1, "$ ", 2) : write(1, "", 0);
	}
	free(buffer);
	return (0);
}
