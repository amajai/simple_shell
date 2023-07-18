#include <stdio.h>
#include <unistd.h>
#include "main.h"

/**
 * error_disp - Prints a command is not valid to the STD_OUT
 * @cmd: Invalid command line arguement
 * @count: number of execution passed in the command line
 * @arg: Name of the executable the shell is run from
 */

void error_disp(char *cmd, unsigned int count, char *arg)
{
	count -= 1;

	write(2, arg, _strlen(arg));
	write(2, ": ", 2);
	write(2, cmd, _strlen(cmd));
	write(2, ": ", 2);
	_putchar(count + '0');
	write(2, ": not found\n", 12);
}
