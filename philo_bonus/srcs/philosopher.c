#include "main.h"

static long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1000 + (int)(tv.tv_usec / 1000));
}

static void	print_status(long time, int who, int something)
{
	if (something == P_TAKEN_FORK)
		printf("%ld %d has taken a fork\n", time, ++who);
	else if (something == P_EATING)
		printf("%ld %d is eating\n", time, ++who);
	else if (something == P_SLEEPING)
		printf("%ld %d is sleeping\n", time, ++who);
	else if (something == P_THINKING)
		printf("%ld %d is thinking\n", time, ++who);
	else if (something == P_DIED)
		printf("%ld %d died\n", time, ++who);
}

static void	change_status(t_params *p, t_phi *me)
{
	if (me->status == P_THINKING
		&& sem_wait(g_sem_philo) == 0)
	{
		me->now_time = get_time();
		print_status(me->now_time, me->i, P_TAKEN_FORK);
		print_status(me->now_time, me->i, P_TAKEN_FORK);
		me->status = P_EATING;
		p->remain_eat_time--;
		me->lasteat_time = me->now_time;
	}
	else if (me->status == P_EATING
		&& me->now_time - me->lasteat_time > p->tteat)
	{
		sem_post(g_sem_philo);
		me->status = P_SLEEPING;
	}
	else if (me->status == P_SLEEPING
		&& me->now_time - me->lasteat_time > p->tteat + p->ttsleep)
		me->status = P_THINKING;
	else
		return ;
	print_status(me->now_time, me->i, me->status);
}

static int	is_finished(t_params *p)
{
	int			i;

	if (p->num_of_times_each_philo_must_eat == -1)
		return (0);
	i = 0;
	while (i < p->num_of_philo)
	{
		if (p->remain_eat_time >= 0)
			return (0);
		i++;
	}
	return (1);
}

void	philosopher(t_params *p, int i)
{
	t_phi		me;

	me.i = i;
	me.lasteat_time = get_time();
	me.status = P_THINKING;
	while (1)
	{
		if (is_finished(p) == 1)
		{
			sem_post(g_sem_dead);
			exit (0);
		}
		me.now_time = get_time();
		if (me.now_time - me.lasteat_time > p->ttdie)
			break ;
		change_status(p, &me);
		usleep(5);
	}
	print_status(me.now_time, me.i, P_DIED);
	sem_post(g_sem_dead);
	exit (0);
}
