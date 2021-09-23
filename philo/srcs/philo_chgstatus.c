/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_chgstatus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 01:52:56 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/23 18:01:26 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	change_status_take_left_fork(t_status *s, int i)
{
	pthread_mutex_lock(&s->fork[i].mtx);
	if (s->fork[i].i == 1)
	{
		s->ph[i].now_time = get_time();
		if (s->ph[i].now_time - s->ph[i].lasteat_time > s->param.ttdie)
			return (ST_PHILO_DEAD);
		s->fork[i].i = 0;
		print_status(s->ph[i].now_time, i, P_TAKEN_FORK);
		s->ph[i].status = P_TAKEN_FORK;
	}
	pthread_mutex_unlock(&s->fork[i].mtx);
	return (P_TAKEN_FORK);
}

static int	change_status_to_eating(t_status *s, int i)
{
	int		ret;

	ret = 0;
	pthread_mutex_lock(&s->fork[(i + 1) % s->param.num_of_philo].mtx);
	if (s->fork[(i + 1) % s->param.num_of_philo].i == 1)
	{
		s->ph[i].now_time = get_time();
		if (s->ph[i].now_time - s->ph[i].lasteat_time > s->param.ttdie)
			return (ST_PHILO_DEAD);
		s->fork[(i + 1) % s->param.num_of_philo].i = 0;
		print_status(s->ph[i].now_time, i, P_TAKEN_FORK);
		s->ph[i].status = P_EATING;
		s->ph[i].lasteat_time = s->ph[i].now_time;
		print_status(s->ph[i].now_time, i, s->ph[i].status);
		ret = P_EATING;
		s->ph[i].eat_cnt++;
		if (s->param.times_must_eat != -1
			&& s->ph[i].eat_cnt >= s->param.times_must_eat)
			s->num_of_philo_ate++;
	}
	pthread_mutex_unlock(&s->fork[(i + 1) % s->param.num_of_philo].mtx);
	return (ret);
}

static int	change_status_to_sleeping(t_status *s, int i)
{
	if (s->ph[i].now_time - s->ph[i].lasteat_time > s->param.tteat)
	{
		pthread_mutex_lock(&s->fork[i].mtx);
		pthread_mutex_lock(&s->fork[(i + 1) % s->param.num_of_philo].mtx);
		s->fork[i].i = 1;
		s->fork[(i + 1) % s->param.num_of_philo].i = 1;
		pthread_mutex_unlock(&s->fork[(i + 1) % s->param.num_of_philo].mtx);
		pthread_mutex_unlock(&s->fork[i].mtx);
		s->ph[i].status = P_SLEEPING;
		s->ph[i].now_time = get_time();
		print_status(s->ph[i].now_time, i, s->ph[i].status);
		return (P_SLEEPING);
	}
	return (0);
}

static int	change_status_to_thinking(t_status *s, int i)
{
	if (s->ph[i].now_time - s->ph[i].lasteat_time
		> (long)s->param.tteat + (long)s->param.ttsleep)
	{
		s->ph[i].status = P_THINKING;
		print_status(s->ph[i].now_time, i, s->ph[i].status);
		return (P_THINKING);
	}
	return (0);
}

int	change_status(t_status *s, int i)
{
	if (s->param.num_of_philo <= 1)
		return (-1);
	if (s->ph[i].status == P_THINKING)
		return (change_status_take_left_fork(s, i));
	if (s->ph[i].status == P_TAKEN_FORK)
		return (change_status_to_eating(s, i));
	else if (s->ph[i].status == P_EATING)
		return (change_status_to_sleeping(s, i));
	else if (s->ph[i].status == P_SLEEPING)
		return (change_status_to_thinking(s, i));
	return (-1);
}
