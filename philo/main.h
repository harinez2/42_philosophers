#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <errno.h>

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

pthread_mutex_t	g_mtx;

typedef struct s_params
{
	int		num_of_philo;
	int		ttdie;
	int		tteat;
	int		ttsleep;
	int		num_of_times_each_philo_must_eat;
	int		i;
	int		fork[MAX_PHILOSPHERS];
	int		remain_eat_time[MAX_PHILOSPHERS];
	int		someone_dead;
}	t_params;

typedef struct s_phi
{
	int		i;
	long	lasteat_time;
	long	now_time;
	int		status;
}	t_phi;

void	*philosopher(void *arg);

int		ft_atoi(char *s, int *errflg);

void	error_exit(int errcode);
void	print_usage_exit(void);

#endif
