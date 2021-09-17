#include "main.h"

// void	print_status(long time, int who, int something)
// {
// 	print_num(time);
// 	ft_putchars(" ");
// 	print_num(++who);
// 	if (something == P_TAKEN_FORK)
// 		ft_putchars(" has taken a fork\n");
// 	else if (something == P_EATING)
// 		ft_putchars(" is eating\n");
// 	else if (something == P_SLEEPING)
// 		ft_putchars(" is sleeping\n");
// 	else if (something == P_THINKING)
// 		ft_putchars(" is thinking\n");
// 	else if (something == P_DIED)
// 		ft_putchars(" died\n");
// }

void	print_status(long time, int who, int something)
{
	who++;
	if (something == P_TAKEN_FORK)
		printf("%ld %d has taken a fork\n", time, who);
	else if (something == P_EATING)
		printf("%ld %d is eating\n", time, who);
	else if (something == P_SLEEPING)
		printf("%ld %d is sleeping\n", time, who);
	else if (something == P_THINKING)
		printf("%ld %d is thinking\n", time, who);
	else if (something == P_DIED)
		printf("%ld %d died\n", time, who);
}

static int	is_in_finished_condition(t_status *s)
{
	// int			i;

	if (s->someone_dead > 0)
		return (1);
	if (s->param.times_must_eat == -1)
		return (0);
	else if (s->param.times_must_eat > 0
		&& s->num_of_philo_ate == s->param.num_of_philo)
	{
		// i = 0;
		// while (i < s->param.num_of_philo)
		// {
		// 	if (s->ph[i].remain_eat_time > 0)
		// 		return (0);
		// 	i++;
		// }
		return (1);
	}
	return (0);
}

// static int	calc_waittime(t_status *s, int i, int diff_time)
// {
// 	unsigned int		seq;
// 	int		order;
// 	int		ret;

// 	seq = diff_time / s->param.tteat;
// 	if (seq % (unsigned int)s->param.num_of_philo == 0)
// 	{
// 		s->ph[i].seq_start_time = s->ph[i].now_time;
// 		seq %= s->param.num_of_philo;
// 	}
// 	order = (i + 1) % 2;
// 	if (seq >= (unsigned int)i + 2 || (seq == 0 && i == s->param.num_of_philo - 1))
// 		order = (order + 1) % 2;
// 	// printf("   i%d:order%d:seq%d:difftime%d:timemusteat%d\n", i, order, seq, diff_time, s->param.tteat);
// 	if (order)
// 		ret = 500;
// 		// return (50);
// 	else
// 		ret = s->param.tteat * 1000;
// 		// return (s->param.tteat * 1000);
// 	// printf("      ret%d\n", ret);
// 	return (ret);
// }

static int	philosopher_doing(t_status *s, int i)
{
	// int			ret;

	// pthread_mutex_lock(&s->mtx);
	if (is_in_finished_condition(s) == 1)
		return (ST_SIMUL_FINISHED);
	s->ph[i].now_time = get_time();
	if (s->ph[i].now_time - s->ph[i].lasteat_time > s->param.ttdie)
		return (ST_PHILO_DEAD);
	// ret = change_status(s, i);
	change_status(s, i);
	// pthread_mutex_unlock(&s->mtx);

	// if (ret == P_EATING)
	// 	usleep_exact(s->param.tteat * 1000);
	// else if (ret == P_SLEEPING)
	// 	usleep_exact(s->param.ttsleep * 1000);
	// else
	usleep_exact(200);
	// usleep_exact(calc_waittime(s, i,
	// 	s->ph[i].now_time - s->ph[i].seq_start_time));
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
		usleep_exact(2000);
		// usleep_exact(s->param.num_of_philo * 10);
	while (1)
	{
		ret = philosopher_doing(s, i);
		if (ret > 0)
			break ;
	}
	if (ret == ST_PHILO_DEAD)
	{
		s->someone_dead++;
		s->dead_time = s->ph[i].now_time;
		print_status(s->ph[i].now_time, i, P_DIED);
	}
	// pthread_mutex_unlock(&s->mtx);
	return (NULL);
}
