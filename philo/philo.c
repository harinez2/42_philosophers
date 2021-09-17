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
	int		finish_flg;

	finish_flg = 0;
	pthread_mutex_lock(&s->mtx);
	if (s->someone_dead > 0)
		finish_flg = 1;
	else if (s->param.times_must_eat > 0
		&& s->num_of_philo_ate == s->param.num_of_philo)
		finish_flg = 1;
	pthread_mutex_unlock(&s->mtx);
	return (finish_flg);
}

static void	sleep_some(t_status *s, int i)
{
	int		haif_time_to_die;

	haif_time_to_die = (s->param.ttdie - s->param.tteat - s->param.ttsleep) / 2;
	if (s->param.num_of_philo % 2 == 0)
		usleep_exact(1000);
	else if (s->ph[i].lasteat_time + haif_time_to_die < s->ph[i].now_time)
		usleep_exact(1000);
	else
		usleep_exact(3000);
}

static int	philosopher_doing(t_status *s, int i)
{
	if (is_in_finished_condition(s) == 1)
		return (ST_SIMUL_FINISHED);
	s->ph[i].now_time = get_time();
	if (s->ph[i].now_time - s->ph[i].lasteat_time > s->param.ttdie)
		return (ST_PHILO_DEAD);
	change_status(s, i);
	sleep_some(s, i);
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
	if (i % 2 == 1)
		usleep_exact(2000);
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
