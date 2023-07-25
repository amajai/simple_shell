#include <sys/wait.h>

/**
 * chkpstatus - gets the status returned from child process
 * @status: shell status value
 *
 * Return: status code
 */
int chkpstatus(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (0);
}
