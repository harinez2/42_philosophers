/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 01:52:37 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/23 17:39:28 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	destroy_param(t_status *s)
{
	int			i;

	i = 0;
	while (i < s->param.num_of_philo)
	{
		pthread_mutex_destroy(&s->fork[i].mtx);
		i++;
	}
	pthread_mutex_destroy(&s->mtx);
}

static void	init_param(t_status *s)
{
	int			i;

	s->start_time = get_time();
	i = 0;
	while (i < s->param.num_of_philo)
	{
		s->ph[i].i = i;
		s->ph[i].lasteat_time = s->start_time;
		s->ph[i].seq_start_time = s->start_time;
		s->ph[i].status = P_THINKING;
		s->ph[i].eat_cnt = 0;
		pthread_mutex_init(&s->fork[i].mtx, NULL);
		s->fork[i].i = 1;
		i++;
	}
	s->someone_dead = 0;
	s->num_of_philo_ate = 0;
	pthread_mutex_init(&s->mtx, NULL);
}

static int	read_param(t_param *p, int argc, char **argv)
{
	if (ft_atoi(argv[1], &p->num_of_philo) == -1)
		return (print_error(ERR_PARAM));
	if (ft_atoi(argv[2], &p->ttdie) == -1)
		return (print_error(ERR_PARAM));
	if (ft_atoi(argv[3], &p->tteat) == -1)
		return (print_error(ERR_PARAM));
	if (ft_atoi(argv[4], &p->ttsleep) == -1)
		return (print_error(ERR_PARAM));
	p->times_must_eat = -1;
	if (argc == 6
		&& ft_atoi(argv[5], &p->times_must_eat) == -1)
		return (print_error(ERR_PARAM));
	if (MAX_PHILOSOPHERS < p->num_of_philo)
		return (print_error(ERR_MAX_PHILOSOPHERS));
	else if (p->num_of_philo < 1 || p->ttdie < 0 || INT_MAX < p->ttdie
		|| p->tteat < 0 || INT_MAX < p->tteat
		|| p->ttsleep < 0 || INT_MAX < p->ttsleep
		|| p->times_must_eat < -1 || INT_MAX < p->times_must_eat)
		return (print_error(ERR_PARAM));
	return (0);
}

int	main(int argc, char **argv)
{
	int				i;
	pthread_t		t[MAX_PHILOSOPHERS];
	t_status		s;

	if (argc < 5 || 6 < argc)
		return (print_error(ERR_PARAM));
	if (read_param(&s.param, argc, argv) == -1)
		return (-1);
	init_param(&s);
	i = 0;
	while (i < s.param.num_of_philo)
	{
		pthread_mutex_lock(&s.mtx);
		s.tmp_i = i;
		pthread_create(&t[i], NULL, philosopher, &s);
		i++;
	}
	i = 0;
	while (i < s.param.num_of_philo)
		pthread_join(t[i++], NULL);
	destroy_param(&s);
	return (0);
}
