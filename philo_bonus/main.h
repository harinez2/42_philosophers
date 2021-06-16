#ifndef MAIN_H
# define MAIN_H

# include <semaphore.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>

# define	SEM_OPEN_RETRY_MAX	10

# define	MAX_PHILOSPHERS		100
# define	P_TAKEN_FORK		1
# define	P_EATING			2
# define	P_SLEEPING			3
# define	P_THINKING			4
# define	P_DIED				5

# define	ERR_MAX_PHILOSPHERS	-1
# define	ERR_SEM_OPEN		-2
# define	ERR_SEM_CLOSE		-3
# define	ERR_FAILED_TO_FORK	-4
# define	ERR_FAILED_TO_WAIT	-5

sem_t	*g_sem_philo;
sem_t	*g_sem_dead;

typedef struct s_params
{
	int		num_of_philo;
	int		ttdie;
	int		tteat;
	int		ttsleep;
	int		num_of_times_each_philo_must_eat;
	int		i;
	int		remain_eat_time;
}	t_params;

typedef struct s_phi
{
	int		i;
	long	lasteat_time;
	long	now_time;
	int		status;
}	t_phi;

void	philosopher(t_params *p, int i);

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_atoi(char *s, int *retnum);

void	error_exit(int errcode);
void	print_usage_exit(void);

#endif
