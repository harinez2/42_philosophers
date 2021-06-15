#include "main.h"

static void	print_usage_exit(void)
{
	printf("Usage:\n");
	printf("    ./philo NUM_OF_PHILO TT_DIE TT_EAT TT_SLEEP [TIMES_MUST_EAT]\n");
	printf("\n");
	printf("Parameters:\n");
	printf("    NUM_OF_PHILO\n");
	printf("        The number of philosophers/forks.\n");
	printf("    TT_DIE\n");
	printf("        The time to die if a philosopher doesn't start eating\n");
	printf("        in milliseconds.\n");
	printf("    TT_EAT\n");
	printf("        The time it takes for a philosopher to eat in millisec.\n");
	printf("    TT_SLEEP\n");
	printf("        The time the philosopher will spend sleeping in\n");
	printf("        millisec.\n");
	printf("    TIMES_MUST_EAT\n");
	printf("        If all philosophers eat at least the specified times,\n");
	printf("        the simulation will stop.\n");
	printf("\n");
	exit (0);
}

static void	open_semaphore(char *sem_name, t_params *p)
{
	int		i;

	ft_strlcpy(sem_name, "/philo0", 8);
	i = 0;
	while (i < SEM_OPEN_RETRY_MAX)
	{
		printf("trying to open sem : %s\n", sem_name);
		g_sem = sem_open(sem_name, O_CREAT | O_EXCL, 0600, p->num_of_philo);
		if (g_sem != SEM_FAILED)
			break ;
		sem_name[6]++;
		i++;
	}
	if (g_sem == SEM_FAILED && i == SEM_OPEN_RETRY_MAX)
		error_exit(ERR_SEM_OPEN);
	sem_unlink(sem_name);
}

static int	init_param(t_params *p, int argc, char **argv)
{
	int			i;

	if (ft_atoi(argv[1], &p->num_of_philo) == -1)
		return (-1);
	if (ft_atoi(argv[2], &p->ttdie) == -1)
		return (-1);
	if (ft_atoi(argv[3], &p->tteat) == -1)
		return (-1);
	if (ft_atoi(argv[4], &p->ttsleep) == -1)
		return (-1);
	p->num_of_times_each_philo_must_eat = -1;
	if (argc == 6
		&& ft_atoi(argv[5], &p->num_of_times_each_philo_must_eat) == -1)
		return (-1);
	i = 0;
	while (i < p->num_of_philo)
	{
		p->remain_eat_time[i] = 0;
		if (p->num_of_times_each_philo_must_eat != -1)
			p->remain_eat_time[i] = p->num_of_times_each_philo_must_eat;
		i++;
	}
	p->someone_dead = 0;
	return (0);
}

static void	create_philosophers(t_params *p)
{
	int			i;
	pid_t		pid;
	pid_t		wait_pid;
	int			status;

	i = 0;
	while (i < p->num_of_philo)
	{
		p->i = i;
		pid = fork();
		if (pid == -1)
			error_exit(ERR_FAILED_TO_FORK);
		else if (pid == 0)
			philosopher(p, i);
		i++;
	}
	status = 0;
	wait_pid = wait(&status);
	if (wait_pid == -1)
		error_exit(ERR_FAILED_TO_WAIT);
}

int	main(int argc, char **argv)
{
	char		sem_name[8];
	int			ret;
	t_params	p;

	if (argc < 5 || 6 < argc)
		print_usage_exit();
	if (init_param(&p, argc, argv) == -1)
		return (-1);
	open_semaphore(sem_name, &p);
	create_philosophers(&p);
	ret = sem_close(g_sem);
	if (ret == -1)
		error_exit(ERR_SEM_CLOSE);
}
