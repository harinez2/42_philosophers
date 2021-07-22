#include "main.h"

static int	check_eatable(t_status *s, int i)
{
	int		left;
	int		right;

	if (s->param.num_of_philo <= 1)
		return (0);
	left = (s->param.num_of_philo + i - 1) % s->param.num_of_philo;
	right = (i + 1) % s->param.num_of_philo;
	if (s->fork[i].i == 1 && s->fork[right].i == 1)
	{
		if (s->ph[left].lasteat_time >= s->ph[i].lasteat_time
			&& s->ph[i].lasteat_time <= s->ph[right].lasteat_time)
		{
			return (1);
		}
	}
	return (0);
}

static void	change_status_to_eating(t_status *s, int i)
{
	if (check_eatable(s, i))
	{
		s->fork[i].i = 0;
		s->fork[(i + 1) % s->param.num_of_philo].i = 0;
		print_status(s->ph[i].now_time, i, P_TAKEN_FORK);
		print_status(s->ph[i].now_time, i, P_TAKEN_FORK);
		s->ph[i].status = P_EATING;
		s->ph[i].remain_eat_time--;
		s->ph[i].lasteat_time = s->ph[i].now_time;
		print_status(s->ph[i].now_time, i, s->ph[i].status);
	}
}

static void	change_status_to_sleeping(t_status *s, int i)
{
	if (s->ph[i].now_time - s->ph[i].lasteat_time > s->param.tteat)
	{
		s->fork[i].i = 1;
		s->fork[(i + 1) % s->param.num_of_philo].i = 1;
		s->ph[i].status = P_SLEEPING;
		print_status(s->ph[i].now_time, i, s->ph[i].status);
	}
}

static void	change_status_to_thinking(t_status *s, int i)
{
	if (s->ph[i].now_time - s->ph[i].lasteat_time
		> s->param.tteat + s->param.ttsleep)
	{
		s->ph[i].status = P_THINKING;
		print_status(s->ph[i].now_time, i, s->ph[i].status);
	}
}

void	change_status(t_status *s, int i)
{
	s->ph[i].now_time = get_time();
	if (s->ph[i].status == P_THINKING)
		change_status_to_eating(s, i);
	else if (s->ph[i].status == P_EATING)
		change_status_to_sleeping(s, i);
	else if (s->ph[i].status == P_SLEEPING)
		change_status_to_thinking(s, i);
}
