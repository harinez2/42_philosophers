#include "main.h"

int	print_error(int errcode)
{
	if (errcode == ERR_PARAM)
		printf("Error: The specified parameter is invalid.\n");
	else if (errcode == ERR_MAX_PHILOSOPHERS)
		printf("Error: The max number of acceptable philosopher is %d.\n",
			MAX_PHILOSOPHERS);
	else if (errcode == ERR_SEM_OPEN)
		printf("Error: The environment value is invalid.\n");
	else if (errcode == ERR_SEM_CLOSE)
		printf("Error: Failed to close semaphore(%d)\n", errno);
	else if (errcode == ERR_FAILED_TO_FORK)
		printf("Error: Failed to fork.\n");
	else if (errcode == ERR_FAILED_TO_WAIT)
		printf("Error: Failed to wait.\n");
	else
		printf("Error\n");
	return (-1);
}
