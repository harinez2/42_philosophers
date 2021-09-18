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
	if (argc == 6
		&& ft_atoi(argv[5], &p->times_must_eat) == -1)
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

static void	create_philosophers(t_param *p, int *pid)
{
	int			i;

	i = 0;
	while (i < p->num_of_philo)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			error_exit(ERR_FAILED_TO_FORK);
		else if (pid[i] == 0)
			philosopher(p, i);
		i++;
	}
}

static void	wait_all_philosophers(t_param *p, int *pid)
{
	int		i;
	int		status;

	if (sem_wait(g_sem_dead) == 0)
	{
		i = 0;
		while (i < p->num_of_philo)
			kill(pid[i++], SIGKILL);
	}
	i = 0;
	while (i < p->num_of_philo)
	{
		if (wait(&status) == -1)
			error_exit(ERR_FAILED_TO_WAIT);
		i++;
	}
	if (sem_close(g_sem_philo) == -1)
		error_exit(ERR_SEM_CLOSE);
	if (sem_close(g_sem_dead) == -1)
		error_exit(ERR_SEM_CLOSE);
}

int	main(int argc, char **argv)
{
	char		sem_philo[8];
	char		sem_dead[8];
	pid_t		pid[MAX_PHILOSOPHERS];
	t_param		p;

	if (argc < 5 || 6 < argc)
		print_usage_exit();
	if (init_param(&p, argc, argv) == -1)
		return (-1);
	if (p.num_of_philo > MAX_PHILOSOPHERS)
		error_exit(ERR_MAX_PHILOSOPHERS);
	ft_strlcpy(sem_philo, "/philo0", 8);
	open_semaphore(sem_philo, p.num_of_philo / 2, &g_sem_philo);
	ft_strlcpy(sem_dead, "/deadd0", 8);
	open_semaphore(sem_dead, 0, &g_sem_dead);
	create_philosophers(&p, pid);
	wait_all_philosophers(&p, pid);
	return (0);
}
