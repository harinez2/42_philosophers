#include "main.h"

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

static void	change_status(t_param *p, t_phi *me)
{
	if (me->status == P_THINKING
		&& sem_wait(g_sem_philo) == 0)
	{
		me->now_time = get_time();
		print_status(me->now_time, me->i, P_TAKEN_FORK);
		print_status(me->now_time, me->i, P_TAKEN_FORK);
		me->status = P_EATING;
		me->eat_cnt++;
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

static int	is_in_finished_condition(t_param *p, t_phi *me)
{
	if (p->times_must_eat != -1
		&& (me->status == P_SLEEPING || me->status == P_THINKING)
		&& me->eat_cnt >= p->times_must_eat)
	{
		return (1);
	}
	return (0);
}

static void	sleep_some(t_param *p, t_phi *me)
{
	int		haif_time_to_die;

	haif_time_to_die = (p->ttdie - p->tteat - p->ttsleep) / 2;
	if (p->num_of_philo % 2 == 0)
		usleep_exact(1000);
	else if (me->lasteat_time + haif_time_to_die < me->now_time)
		usleep_exact(1000);
	else
		usleep_exact(3000);
}

void	philosopher(t_param *p, int i)
{
	t_phi		me;

	me.i = i;
	me.now_time = get_time();
	me.lasteat_time = me.now_time;
	me.status = P_THINKING;
	me.eat_cnt = 0;
	while (1)
	{
		if (is_in_finished_condition(p, &me) == 1)
		{
			sem_post(g_sem_ate);
			exit (0);
		}
		me.now_time = get_time();
		if (me.now_time - me.lasteat_time > p->ttdie)
			break ;
		change_status(p, &me);
		sleep_some(p, &me);
	}
	print_status(me.now_time, me.i, P_DIED);
	sem_post(g_sem_dead);
	exit (0);
}
