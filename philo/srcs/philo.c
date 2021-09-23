/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 01:52:59 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/23 15:27:06 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

static int	philosopher_doing(t_status *s, int i)
{
	if (is_in_finished_condition(s) == 1)
		return (ST_SIMUL_FINISHED);
	s->ph[i].now_time = get_time();
	if (s->ph[i].now_time - s->ph[i].lasteat_time > s->param.ttdie)
		return (ST_PHILO_DEAD);
	change_status(s, i);
	usleep_exact(500);
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
		pthread_mutex_lock(&s->mtx);
		s->someone_dead++;
		s->dead_time = s->ph[i].now_time;
		pthread_mutex_unlock(&s->mtx);
		print_status(s->ph[i].now_time, i, P_DIED);
	}
	return (NULL);
}
