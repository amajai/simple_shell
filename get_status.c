#include <sys/wait.h>

/**
 * get_status - gets status based on res value
 * @res: function response value
 *
 * Return: status code
 */
int get_status(int res)
{
	if (res == 1)
		return (127);
	else
		return (0);
}
