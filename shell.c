#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/**
 * main - Breaks down arguement entered
 * @ac: number of arguements
 * @av: arguements entered
 * @env: bash enviroments
 * Return: 0
 */

int main(int ac, char **av, char **env)
{
	size_t n = 0;
	char *buffer = NULL;
	char **cmds = NULL;
	char *token;
	int cmd;
	pid_t pid;
	int status = 0;

	write(1, "$ ", 2);
	while ((cmd = getline(&buffer, &n, stdin)) != EOF)
	{
		cmds = malloc(sizeof(char *) * 2);
		token = strtok(buffer, "\n");
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
				return (1);
			}
		}
		else
		{
			wait(&status);
		}
		free(cmds);
		write(1, "$ ", 2);
	}

	return (0);
}
