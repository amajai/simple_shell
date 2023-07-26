#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

/**
 * process_alias - gets alias args from command line process the commands
 * @alias_cmdline: command line buffer.
 * @aliases: list of aliases.
 * @alias_c: alias count
 * Return: Nothing
 */
int process_alias(char *alias_cmdline, struct alias ***aliases, int *alias_c)
{
	char **args, *name = NULL, *value = NULL;
	int i = 0;

	args = get_alias_args(alias_cmdline);
	trim(&args[i]);
	if (_strcmp(args[i], "alias") != 0)
	{
		freelist(args);
		return (0);
	}
	i++;
	while (args[i] != NULL)
	{
		trim(&args[i]);
		if (_strcmp(args[i], "alias") != 0)
		{
			if (check_d_alias(args[i]) == 0)
			{
				name = strtok(args[i], "='\"");
				value = strtok(NULL, "='\"");
				add_alias(aliases, name, value, alias_c);
			}
			else
				print_alias(args[i], *aliases);
		}
		else
		{
			print_alias(args[i], *aliases);
		}
		i++;
	}
	if (i == 1)
		print_all_alias(*aliases);
	freelist(args);
	return (0);
}

/**
 * get_alias_args - gets alias arguments from command line to an array format
 * with NULL at the end of an array.
 * @alias_cmdline: command line buffer.
 *
 * Return: array of alias arguments
 */
char **get_alias_args(char *alias_cmdline)
{
	int i = 0, arg_count = 0, inside_quotes = 0, cac = 0, max_size = 100;
	char *t, **arr, *ac;

	arr = malloc(sizeof(char *) * max_size);
	ac = alias_cmdline;
	while (alias_cmdline[i] != '\0' && alias_cmdline[i] != '\n')
	{
		if (alias_cmdline[i] == '\'' || alias_cmdline[i] == '\"')
		{
			inside_quotes = !inside_quotes;
			i++;
			cac++;
			continue;
		}
		if (alias_cmdline[i] == ' ' && !inside_quotes)
		{
			if (cac > 0)
			{
				ac[cac] = '\0';
				t = ac;
				arr[arg_count] = _strdup(t);
				ac = ac + cac + 1;
				arg_count++;
				cac = 0;
			}
		}
		else
			cac++;
		i++;
	}
	if (cac > 0)
	{
		t = ac;
		arr[arg_count] = _strdup(t);
		ac = ac + cac;
		arg_count++;
		cac = 0;
	}
	arr[arg_count] = NULL;
	return (arr);
}

/**
 * add_alias - add alias name and value to list of aliases
 * @aliases: array of aliases
 * @name: alias name to add
 * @value: alias value to add
 * @alias_c: alias count
 *
 * Return: Nothing
 */
void add_alias(struct alias ***aliases, char *name, char *value, int *alias_c)
{
	int i = 0;
	unsigned int old_size, new_size;
	struct alias *new_alias = malloc(sizeof(struct alias));

	if (*aliases != NULL)
	{
		while ((*aliases)[i] != NULL)
		{
			if (_strcmp(name, (*aliases)[i]->name) == 0)
			{
				free((*aliases)[i]->value);
				(*aliases)[i]->value = _strdup(value);
				free(new_alias);
				return;
			}
			i++;
		}
	}
	new_alias->name = _strdup(name);
	new_alias->value = _strdup(value);
	if (*aliases == NULL)
	{
		*aliases = malloc(sizeof(struct alias) * 2);
		(*aliases)[0] = new_alias;
		(*aliases)[(*alias_c)] = NULL;
	}
	else
	{
		old_size = sizeof(struct alias) * (*alias_c);
		new_size = sizeof(struct alias) * ((*alias_c) + 1);
		*aliases = _realloc(*aliases, old_size, new_size);
		(*aliases)[(*alias_c)++] = new_alias;
		(*aliases)[(*alias_c)] = NULL;
	}
}

/**
 * print_alias - output the alias name with value
 * @alias: alias name
 * @aliases: array of aliases
 *
 * Return: Nothing
 */
void print_alias(char *alias, struct alias **aliases)
{
	int is_found = 1, i = 0;
	char *name, *value;

	if (aliases != NULL)
	{
		while (aliases[i] != NULL)
		{
			if (strcmp(alias, aliases[i]->name) == 0)
			{
				name = aliases[i]->name;
				value = aliases[i]->value;
				write(1, name, _strlen(name));
				write(1, "='", 2);
				write(1, value, _strlen(value));
				write(1, "'\n", 2);
				is_found = 0;
				break;
			}
			i++;
		}
	}
	if (is_found == 1)
	{
		write(1, "alias: ", 7);
		write(1, alias, _strlen(alias));
		write(1, " not found\n", 11);
	}
}

/**
 * print_all_alias - output list of aliases
 * @aliases: array of aliases
 *
 * Return: Nothing
 */
void print_all_alias(struct alias **aliases)
{
	int i = 0;
	char *name, *value;

	if (aliases != NULL)
	{
		while (aliases[i] != NULL)
		{
			name = aliases[i]->name;
			value = aliases[i]->value;
			write(1, name, _strlen(name));
			write(1, "='", 2);
			write(1, value, _strlen(value));
			write(1, "'\n", 2);
			i++;
		}
	}
}
