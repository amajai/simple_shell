#include <stdio.h>
#include <stdlib.h>

/**
* freelist - free all the allocated memory of an array/list
* @arr: an array with allocated memories
*
* Return: Nothing
*/
void freelist(char **arr)
{
	int i = 0;

	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
