#include "main.h"

#include <stdio.h>
#include <errno.h>

sem_t	*open_semaphore(char *sem_name)
{
	sem_t	*sem;
	int		i;

	i = 0;
	ft_strlcpy(sem_name, "philo00", 7);
	while (i < RETRY_MAX)
	{
		printf("trying to open sem : %s\n", sem_name);
		sem = sem_open(sem_name, O_CREAT | O_EXCL);
		if (sem != SEM_FAILED)
			break ;
		sem_name[5]++;
		i++;
	}
	if (sem == SEM_FAILED && i == RETRY_MAX)
	{
		printf("semopen error\n");
		exit (-1);
	}
	return (sem);
}

int	main(void)
{
	sem_t	*sem;
	char	sem_name[7];
	int		ret;

	sem = open_semaphore(sem_name);
	//+1 sem_post
	//-1 sem_wait
	ret = sem_close(sem);
	if (ret == -1)
		printf("sem close error:%d\n", errno);
	//sem_unlink

}
