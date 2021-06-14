#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>

#include <stdio.h>
#include <errno.h>

# define RETRY_MAX		10

size_t	ft_strlen(const char *str)
{
	size_t		i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;

	i = 0;
	while (i + 1 < dstsize)
	{
		dst[i] = src[i];
		if (src[i] == '\0')
			break ;
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

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
