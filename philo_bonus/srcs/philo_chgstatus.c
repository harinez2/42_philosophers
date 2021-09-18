#include "main.h"

int	change_status(t_param *p, t_phi *me)
{
	if (p->num_of_philo <= 1)
		return (-1);
	if (me->status == P_THINKING && sem_wait(g_sem_philo) == 0)
	{
		me->now_time = get_time();
		if (me->now_time - me->lasteat_time > p->ttdie)
			return (-1);
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
		return (0);
	print_status(me->now_time, me->i, me->status);
	return (0);
}
