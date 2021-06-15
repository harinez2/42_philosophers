#include "main.h"

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
		p->fork[i] = 1;
		p->remain_eat_time[i] = 0;
		if (p->num_of_times_each_philo_must_eat != -1)
			p->remain_eat_time[i] = p->num_of_times_each_philo_must_eat;
		i++;
	}
	p->someone_dead = 0;
	return (0);
}

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

int	main(int argc, char **argv)
{
	int				i;
	pthread_t		t[MAX_PHILOSPHERS];
	t_params		p;

	if (argc < 5 || 6 < argc)
		print_usage_exit();
	if (init_param(&p, argc, argv) == -1)
		return (-1);
	i = 0;
	while (i < p.num_of_philo)
	{
		pthread_mutex_lock(&g_mtx);
		p.i = i;
		pthread_create(&t[i], NULL, philosopher, &p);
		i++;
	}
	i = 0;
	while (i < p.num_of_philo)
		pthread_join(t[i++], NULL);
	return (0);
}
