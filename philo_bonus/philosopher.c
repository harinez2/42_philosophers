#include "main.h"

static long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1000 + (int)(tv.tv_usec / 1000));
}

static void	print_status(long time, int who, int something)
{
	printf("%ld %d ", time, ++who);
	if (something == P_TAKEN_FORK)
		printf("has taken a fork\n");
	else if (something == P_EATING)
		printf("is eating\n");
	else if (something == P_SLEEPING)
		printf("is sleeping\n");
	else if (something == P_THINKING)
		printf("is thinking\n");
	else if (something == P_DIED)
		printf("died\n");
}

static void	change_status(t_params *p, t_phi *me)
{
	if (me->status == P_THINKING
		&& sem_wait(g_sem) == 0)
	{
		print_status(me->now_time, me->i, P_TAKEN_FORK);
		me->status = P_EATING;
		p->remain_eat_time[me->i]--;
		me->now_time = get_time();
		me->lasteat_time = me->now_time;
	}
	else if (me->status == P_EATING
		&& me->now_time - me->lasteat_time > p->tteat)
	{
		sem_post(g_sem);
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

	if (p->someone_dead > 0)
		return (1);
	if (p->num_of_times_each_philo_must_eat == -1)
		return (0);
	i = 0;
	while (i < p->num_of_philo)
	{
		if (p->remain_eat_time[i] > 0)
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
			exit (0);
		me.now_time = get_time();
		if (me.now_time - me.lasteat_time > p->ttdie)
			break ;
		change_status(p, &me);
		usleep(5);
	}
	print_status(me.now_time, me.i, P_DIED);
	p->someone_dead++;
	exit (0);
}