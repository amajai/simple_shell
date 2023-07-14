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
	char *buffer = NULL, *token, *dupbuff;
	int cmd, status;

	(void)ac;
	isatty(STDIN_FILENO) ? write(1, "$ ", 2) : write(1, "", 0);
	while ((cmd = getline(&buffer, &n, stdin)) != EOF)
	{
		dupbuff = _strdup(buffer);
		token = strtok(dupbuff, " \n");
		pid = fork();
		if (pid == -1)
		{
			perror("Error:");
			return (1);
		}
		else if (pid == 0)
			execute(token, buffer, env, av[0]);
		else
			wait(&status);
		free(dupbuff);
		isatty(STDIN_FILENO) ? write(1, "$ ", 2) : write(1, "", 0);
	}
	free(buffer);
	return (0);
}

/**
 * execute - execute program through execve function for a given path.
 * @ppath: program path name.
 * @buffer: stored input line from stdin stream.
 * @env: shell environment list.
 * @execname: Name of the executable the shell is run from.
 *
 * Return: Nothing
 */
void execute(char *ppath, char *buffer, char **env, char *execname)
{
	int i = 0, j = 0, arg_count = 0;
	char **argv;
	char *token;

	while (buffer[j] != '\0')
	{
		if (buffer[j] == ' ')
			arg_count++;
		j++;
	}
	arg_count++;
	argv = malloc(sizeof(char *) * (arg_count + 1));
	if (argv == NULL)
		exit(EXIT_FAILURE);
	argv[i] = ppath;
	token = strtok(buffer, " \n");
	while (token != NULL)
	{
		token = strtok(NULL, " \n");
		argv[++i] = token;
	}
	argv[i] = NULL;
	if (execve(argv[0], argv, env) == EOF)
	{
		perror(execname);
		free(ppath);
		free(argv);
		free(buffer);
		exit(EXIT_FAILURE);
	}
}
