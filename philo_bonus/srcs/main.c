/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 20:44:09 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/19 20:44:09 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	init_param(t_param *p, int argc, char **argv)
{
	if (ft_atoi(argv[1], &p->num_of_philo) == -1)
		return (-1);
	if (ft_atoi(argv[2], &p->ttdie) == -1)
		return (-1);
	if (ft_atoi(argv[3], &p->tteat) == -1)
		return (-1);
	if (ft_atoi(argv[4], &p->ttsleep) == -1)
		return (-1);
	p->times_must_eat = -1;
	if (argc == 6 && ft_atoi(argv[5], &p->times_must_eat) == -1)
		return (-1);
	return (0);
}

static void	open_semaphore(char *sem_name, int sem_cnt, sem_t **sem)
{
	int		i;

	i = 0;
	while (i < SEM_OPEN_RETRY_MAX)
	{
		*sem = sem_open(sem_name, O_CREAT | O_EXCL, 0600, sem_cnt);
		if (*sem != SEM_FAILED)
			break ;
		sem_name[6]++;
		i++;
	}
	if (*sem == SEM_FAILED && i == SEM_OPEN_RETRY_MAX)
		error_exit(ERR_SEM_OPEN);
	sem_unlink(sem_name);
}

static void	close_all_semaphore(void)
{
	if (sem_close(g_sem_philo) == -1)
		error_exit(ERR_SEM_CLOSE);
	if (sem_close(g_sem_dead) == -1)
		error_exit(ERR_SEM_CLOSE);
	if (sem_close(g_sem_ate) == -1)
		error_exit(ERR_SEM_CLOSE);
}

static void	create_philosophers(t_param *p)
{
	int			i;

	i = 0;
	while (i < p->num_of_philo)
	{
		p->pid[i] = fork();
		if (p->pid[i] == -1)
			error_exit(ERR_FAILED_TO_FORK);
		else if (p->pid[i] == 0)
			philosopher(p, i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char		sem_philo[8];
	char		sem_dead[8];
	char		sem_ate[8];

	if (argc < 5 || 6 < argc)
		print_usage_exit();
	if (init_param(&g_p, argc, argv) == -1)
		return (-1);
	if (g_p.num_of_philo > MAX_PHILOSOPHERS)
		error_exit(ERR_MAX_PHILOSOPHERS);
	ft_strlcpy(sem_philo, "/philo0", 8);
	open_semaphore(sem_philo, g_p.num_of_philo / 2, &g_sem_philo);
	ft_strlcpy(sem_dead, "/deadd0", 8);
	open_semaphore(sem_dead, 0, &g_sem_dead);
	ft_strlcpy(sem_dead, "/ateee0", 8);
	open_semaphore(sem_ate, 0, &g_sem_ate);
	create_philosophers(&g_p);
	wait_all_philosophers(&g_p);
	close_all_semaphore();
	return (0);
}
