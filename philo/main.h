/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 01:52:42 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/18 01:52:42 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define	ST_PHILO_DEAD		1
# define	ST_SIMUL_FINISHED	2

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
	long		seq_start_time;
	long		lasteat_time;
	long		now_time;
	int			status;
	long		eat_cnt;
}	t_phi;

typedef struct s_status
{
	long			start_time;
	t_fork			fork[MAX_PHILOSOPHERS];
	int				someone_dead;
	long			dead_time;
	int				num_of_philo_ate;
	t_phi			ph[MAX_PHILOSOPHERS];
	t_param			param;
	int				tmp_i;
	pthread_mutex_t	mtx;
}	t_status;

// error.c
int			print_error(int errcode);
// libft.c
size_t		ft_strlen(const char *str);
void		ft_putchars(char *s);
void		print_num(long d);
int			ft_atoi(char *s, int *retnum);
// libutil.c
long		get_time(void);
void		usleep_exact(long time_in_usec);
// main.c
int			main(int argc, char **argv);
// philo.c
void		print_status(long time, int who, int something);
void		*philosopher(void *arg);
// philo_behavior.c
int			change_status(t_status *s, int i);

#endif
