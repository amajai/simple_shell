#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
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
	char *buffer = NULL, *token, *dupbuff, *ppath;
	int cmd, status;

	(void)ac;
	isatty(STDIN_FILENO) ? write(1, "$ ", 2) : write(1, "", 0);
	while ((cmd = getline(&buffer, &n, stdin)) != EOF)
	{
		dupbuff = _strdup(buffer);
		token = strtok(dupbuff, " \n");
		ppath = process_input(token, buffer);
		if (ppath != NULL)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("Error:");
				return (1);
			}
			else if (pid == 0)
				execute(ppath, buffer, env, av[0]);
			else
				wait(&status);
		}
		free(ppath);
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

/**
* process_input - checks if pname input is a valid program path.
* @pname: program name
*
* Return: pname or new path if succesful
* NULL if pname is not a valid program path
*/
char *process_input(char *pname, char *buffer)
{
	struct stat st;
	char *token, *new_path, *paths;
	unsigned int token_len, pname_len;

	if (stat(pname, &st) == 0)
		return (_strdup(pname));
	if (_strcmp("exit", pname) == 0)
	{
		free(buffer);
		free(pname);
		exit(0);
	}

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
			return (new_path);
		}
		free(new_path);
		token = strtok(NULL, ":");
	}
	free(paths);
	return (NULL);
}
