#include "main.h"

void	print_status(long time, int who, int something)
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

static int	is_in_finished_condition(t_status *s)
{
	int			i;

	if (s->someone_dead > 0)
		return (1);
	if (s->param.times_must_eat == -1)
		return (0);
	else
	{
		i = 0;
		while (i < s->param.num_of_philo)
		{
			if (s->ph[i].remain_eat_time > 0)
				return (0);
			i++;
		}
		return (1);
	}
}

void	*philosopher(void *arg)
{
	t_status	*s;
	int			i;

	s = (t_status *)arg;
	i = s->tmp_i;
	pthread_mutex_unlock(&s->mtx);
	while (1)
	{
		if (is_in_finished_condition(s) == 1)
			return (NULL);
		s->ph[i].now_time = get_time();
		if (s->ph[i].now_time - s->ph[i].lasteat_time > s->param.ttdie)
			break ;
		pthread_mutex_lock(&s->mtx);
		change_status(s, i);
		pthread_mutex_unlock(&s->mtx);
		usleep(5);
	}
	pthread_mutex_lock(&s->mtx);
	s->someone_dead++;
	pthread_mutex_unlock(&s->mtx);
	print_status(s->ph[i].now_time, i, P_DIED);
	return (NULL);
}
