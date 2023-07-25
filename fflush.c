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
	char count_str[4];
	int temp = count - 1;
	int digit_count = 0;

	while (temp != 0)
	{
		digit_count++;
		temp /= 10;
	}
	temp = count - 1;
	count_str[digit_count] = '\0';
	while (digit_count > 0)
	{
		digit_count--;
		count_str[digit_count] = temp % 10 + '0';
		temp /= 10;
	}
	write(2, arg, _strlen(arg));
	write(2, ": ", 2);
	write(2, count_str, _strlen(count_str));
	write(2, ": ", 2);
	write(2, cmd, _strlen(cmd));
	write(2, ": not found\n", 12);
}
