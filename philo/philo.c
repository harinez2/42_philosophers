#include "main.h"

void	print_status(long time, int who, int something)
{
	print_num(time);
	ft_putchars(" ");
	print_num(++who);
	if (something == P_TAKEN_FORK)
		ft_putchars(" has taken a fork\n");
	else if (something == P_EATING)
		ft_putchars(" is eating\n");
	else if (something == P_SLEEPING)
		ft_putchars(" is sleeping\n");
	else if (something == P_THINKING)
		ft_putchars(" is thinking\n");
	else if (something == P_DIED)
		ft_putchars(" died\n");
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

static int	philosopher_doing(t_status *s, int i)
{
	int			ret;

	pthread_mutex_lock(&s->mtx);
	if (is_in_finished_condition(s) == 1)
		return (2);
	s->ph[i].now_time = get_time();
	if (s->ph[i].now_time - s->ph[i].lasteat_time > s->param.ttdie)
		return (1);
	ret = change_status(s, i);
	pthread_mutex_unlock(&s->mtx);
	if (ret == P_EATING)
		usleep(s->param.tteat);
	else if (ret == P_SLEEPING)
		usleep(s->param.ttsleep);
	else
		usleep(5);
	return (0);
}

void	*philosopher(void *arg)
{
	t_status	*s;
	int			i;
	int			ret;

	s = (t_status *)arg;
	i = s->tmp_i;
	pthread_mutex_unlock(&s->mtx);
	if (i % 2 == 0)
		usleep(s->param.tteat - 20);
	while (1)
	{
		ret = philosopher_doing(s, i);
		if (ret > 0)
			break ;
	}
	if (ret == 1)
	{
		s->someone_dead++;
		s->dead_time = s->ph[i].now_time;
		print_status(s->ph[i].now_time, i, P_DIED);
	}
	pthread_mutex_unlock(&s->mtx);
	return (NULL);
}
