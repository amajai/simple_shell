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
	char *buffer = NULL;
	int cmd, ps;
	alias_t **aliases = NULL;

	(void)ac;
	isatty(STDIN_FILENO) ? write(1, "$ ", 2) : write(1, "", 0);
	while ((cmd = getline(&buffer, &n, stdin)) != EOF)
	{
		ps = process_cmds(buffer, av[0], env, &aliases);
		isatty(STDIN_FILENO) ? write(1, "$ ", 2) : write(1, "", 0);
	}
	if (aliases != NULL)
		free_all_alias(aliases);
	free(buffer);
	return (ps);
}
/**
 * process_cmds - Process input command line.
 * @buffer: command line string
 * @exec: shell executable filename
 * @env: environment variables
 * @as: list of aliases
 *
 * Return: 0
 */
int process_cmds(char *buffer, char *exec, char **env, alias_t ***as)
{
	char *ppath = NULL, **cmds;
	int i = 0, status, ps = 0;
	pid_t pid;
	static int alias_count = 1;

	cmds = get_cmds(buffer);
	while (cmds[i] != NULL)
	{
		if (_strncmp("alias", cmds[i], 5) == 0)
			process_alias(cmds[i], as, &alias_count);
		else if (_strncmp("exit", cmds[i], 4) == 0)
			exit_call(buffer, cmds, as);
		else
			ppath = p_input(cmds[i], exec, env);
		if (ppath != NULL)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("Error:");
				return (1);
			}
			else if (pid == 0)
				execute(ppath, cmds[i], env, exec);
			else
				waitpid(pid, &status, 0);
			ps = chkpstatus(status);
		}
		else
			ps = 127;
		if (ppath != NULL)
			free(ppath);
		i++;
	}
	freelist(cmds);
	return (ps);
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
	token = strtok(buffer, " \n");
	argv[i] = token;
	while (token != NULL)
	{
		token = strtok(NULL, " \n");
		argv[++i] = token;
	}

	if (execve(ppath, argv, env) == EOF)
	{
		perror(execname);
		free(ppath);
		free(argv);
		free(buffer);
		exit(EXIT_FAILURE);
	}
}

/**
 * exit_call - exit the shell
 * @buffer: commands inputed
 * @cmds: array of buffers
 * @as: list of aliases
 */

void exit_call(char *buffer, char **cmds, alias_t ***as)
{
	int num = 0;
	char *token;

	token = strtok(buffer, " \n");
	token = strtok(NULL, " \n");
	if (token != NULL)
		num = _atoi(token);
	free(buffer);
	freelist(cmds);
	if((*as) != NULL)
		free_all_alias(*as);
	exit(num);
}

/**
* p_input - checks if pname input is a valid program path.
* @buf: program name
* @arg: Name of the executable the shell is run from
* @env: array of environment variables.
* Return: pname or new path if succesful
* NULL if pname is not a valid program path
*/
char *p_input(char *buf, char *arg, char **env)
{
	struct stat st;
	char *path, *pname, *dupbuf;
	static unsigned int count_cmds = 1;

	dupbuf = _strdup(buf);
	pname = strtok(dupbuf, " \n");
	count_cmds++;
	if (_strchr(buf, '/') != NULL)
	{
		if (stat(pname, &st) == 0)
			return (_strdup(pname));
	}
	else
	{
		if (env == NULL || _getenv("PATH") == NULL)
		{
			error_disp(pname, count_cmds, arg);
			free(dupbuf);
			return (NULL);
		}
		path = get_path(pname, dupbuf);
		if (path != NULL)
			return (path);
		error_disp(pname, count_cmds, arg);
		free(dupbuf);
	}
	return (NULL);
}
