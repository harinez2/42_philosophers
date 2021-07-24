#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <errno.h>
# include <limits.h>

# define	MAX_PHILOSOPHERS	200
# define	P_TAKEN_FORK		1
# define	P_EATING			2
# define	P_SLEEPING			3
# define	P_THINKING			4
# define	P_DIED				5

# define	ERR_PARAM				-1
# define	ERR_MAX_PHILOSOPHERS	-2
# define	ERR_SEM_OPEN			-3
# define	ERR_SEM_CLOSE			-4
# define	ERR_FAILED_TO_FORK		-5
# define	ERR_FAILED_TO_WAIT		-6

typedef struct s_param
{
	int		num_of_philo;
	int		ttdie;
	int		tteat;
	int		ttsleep;
	int		times_must_eat;
}	t_param;

typedef struct s_fork
{
	int				i;
	pthread_mutex_t	mtx;
}	t_fork;

typedef struct s_phi
{
	int			i;
	long		lasteat_time;
	long		now_time;
	int			status;
	int			remain_eat_time;
}	t_phi;

typedef struct s_status
{
	long			start_time;
	t_fork			fork[MAX_PHILOSOPHERS];
	int				someone_dead;
	long			dead_time;
	t_phi			ph[MAX_PHILOSOPHERS];
	t_param			param;
	int				tmp_i;
	pthread_mutex_t	mtx;
}	t_status;

int		change_status(t_status *s, int i);

void	print_status(long time, int who, int something);
void	*philosopher(void *arg);

size_t	ft_strlen(const char *str);
void	ft_putchars(char *s);
void	print_num(long d);
int		ft_atoi(char *s, int *errflg);

long	get_time(void);

int		print_error(int errcode);
void	print_usage_exit(void);

#endif
