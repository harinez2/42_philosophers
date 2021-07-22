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

static int	check_eatable(t_status *s, int i)
{
	int		left;
	int		right;

	left = (s->param.num_of_philo + i - 1) % s->param.num_of_philo;
	right = (i + 1) % s->param.num_of_philo;
	if (s->fork[i] == 1 && s->fork[right] == 1)
	{
		if (s->ph[left].lasteat_time >= s->ph[i].lasteat_time
			&& s->ph[i].lasteat_time <= s->ph[right].lasteat_time)
		{
			return (1);
		}
	}
	return (0);
}

static void	change_status(t_status *s, int i)
{
	s->ph[i].now_time = get_time();
	if (s->ph[i].status == P_THINKING && check_eatable(s, i))
	{
		s->fork[i] = 0;
		s->fork[(i + 1) % s->param.num_of_philo] = 0;
		print_status(s->ph[i].now_time, i, P_TAKEN_FORK);
		print_status(s->ph[i].now_time, i, P_TAKEN_FORK);
		s->ph[i].status = P_EATING;
		s->ph[i].remain_eat_time--;
		s->ph[i].lasteat_time = s->ph[i].now_time;
	}
	else if (s->ph[i].status == P_EATING
		&& s->ph[i].now_time - s->ph[i].lasteat_time > s->param.tteat)
	{
		s->fork[i] = 1;
		s->fork[(i + 1) % s->param.num_of_philo] = 1;
		s->ph[i].status = P_SLEEPING;
	}
	else if (s->ph[i].status == P_SLEEPING
		&& s->ph[i].now_time - s->ph[i].lasteat_time
		> s->param.tteat + s->param.ttsleep)
		s->ph[i].status = P_THINKING;
	else
		return ;
	print_status(s->ph[i].now_time, i, s->ph[i].status);
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
