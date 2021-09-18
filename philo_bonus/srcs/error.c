#include "main.h"

void	error_exit(int errcode)
{
	if (errcode == ERR_MAX_PHILOSOPHERS)
		printf("Error: The max number of acceptable philosopher is %d.\n",
			MAX_PHILOSOPHERS);
	else if (errcode == ERR_SEM_OPEN)
		printf("Error: The environment value is invalid.\n");
	else if (errcode == ERR_SEM_CLOSE)
		printf("Error: Failed to close semaphore(%d)\n", errno);
	else if (errcode == ERR_SEM_WAIT)
		printf("Error: Failed to wait semaphore(%d)\n", errno);
	else if (errcode == ERR_FAILED_TO_FORK)
		printf("Error: Failed to fork.\n");
	else if (errcode == ERR_FAILED_TO_WAIT)
		printf("Error: Failed to wait.\n");
	else
		printf("Error\n");
	exit(-1);
}

void	print_usage_exit(void)
{
	printf("Usage:\n");
	printf("    ./philo NUM_OF_PHILO TT_DIE TT_EAT TT_SLEEP [TIMES_MUST_EAT]\n");
	printf("\n");
	printf("Parameters:\n");
	printf("    NUM_OF_PHILO\n");
	printf("        The number of philosophers/forks.\n");
	printf("    TT_DIE\n");
	printf("        The time to die if a philosopher doesn't start eating\n");
	printf("        in milliseconds.\n");
	printf("    TT_EAT\n");
	printf("        The time it takes for a philosopher to eat in millisec.\n");
	printf("    TT_SLEEP\n");
	printf("        The time the philosopher will spend sleeping in\n");
	printf("        millisec.\n");
	printf("    TIMES_MUST_EAT\n");
	printf("        If all philosophers eat at least the specified times,\n");
	printf("        the simulation will stop.\n");
	printf("\n");
	exit (0);
}
