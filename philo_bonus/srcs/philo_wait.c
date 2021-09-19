/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 20:44:18 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/19 20:44:18 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	kill_all_process(t_param *p)
{
	int		i;

	i = 0;
	while (i < p->num_of_philo)
		kill(p->pid[i++], SIGKILL);
}

static void	*wait_someone_dead(void *arg)
{
	t_param		*p;
	int			i;

	p = (t_param *)arg;
	if (DBG)
		printf("  started wait_someone_dead().\n");
	if (sem_wait(g_sem_dead) != 0)
		error_exit(ERR_SEM_WAIT);
	if (DBG)
		printf("    sem_wait g_sem_dead catched.\n");
	kill_all_process(p);
	i = 0;
	while (i < p->num_of_philo)
	{
		sem_post(g_sem_ate);
		i++;
	}
	if (DBG)
		printf("  finished wait_someone_dead().\n");
	return (NULL);
}

static void	*wait_all_ate(void *arg)
{
	t_param		*p;
	int			i;

	p = (t_param *)arg;
	if (DBG)
		printf("  started wait_all_ate().\n");
	i = 0;
	while (i < p->num_of_philo)
	{
		if (sem_wait(g_sem_ate) != 0)
			error_exit(ERR_SEM_WAIT);
		if (DBG)
			printf("    sem_wait g_sem_ate catched.\n");
		i++;
	}
	kill_all_process(p);
	sem_post(g_sem_dead);
	if (DBG)
		printf("  started wait_all_ate().\n");
	return (NULL);
}

void	wait_all_philosophers(t_param *p)
{
	int			i;
	pthread_t	t[2];
	int			status;

	pthread_create(&t[0], NULL, wait_someone_dead, p);
	pthread_create(&t[1], NULL, wait_all_ate, p);
	i = 0;
	while (i < 2)
	{
		pthread_join(t[i++], NULL);
		if (DBG)
			printf("  pthread_join joined.\n");
	}
	i = 0;
	while (i < 2)
		pthread_detach(t[i++]);
	i = 0;
	while (i < p->num_of_philo)
	{
		if (waitpid(p->pid[i], &status, WNOHANG | WUNTRACED) == -1)
			error_exit(ERR_FAILED_TO_WAIT);
		i++;
	}
}
