#include "main.h"

#include <stdio.h>
#include <errno.h>

sem_t	*open_semaphore(char *sem_name)
{
	sem_t	*sem;
	int		i;

	i = 0;
	ft_strlcpy(sem_name, "philo00", 7);
	while (i < SEM_OPEN_RETRY_MAX)
	{
		printf("trying to open sem : %s\n", sem_name);
		sem = sem_open(sem_name, O_CREAT | O_EXCL);
		if (sem != SEM_FAILED)
			break ;
		sem_name[5]++;
		i++;
	}
	if (sem == SEM_FAILED && i == SEM_OPEN_RETRY_MAX)
	{
		printf("Error: Failed to open semaphore(%d)\n", errno);
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

	ret = sem_post(sem);
	printf("post:%d\n", ret);
	ret = sem_post(sem);
	printf("post:%d\n", ret);
	ret = sem_post(sem);
	printf("post:%d\n", ret);
	ret = sem_wait(sem);
	printf("wait:%d\n", ret);
	ret = sem_wait(sem);
	printf("wait:%d\n", ret);
	
	ret = sem_close(sem);
	if (ret == -1)
	{
		printf("Error: Failed to close semaphore(%d)\n", errno);
		exit (-1);
	}
	ret =  sem_unlink(sem_name);
	printf("unlinked:%d\n", ret);
	//sem_unlink

}
