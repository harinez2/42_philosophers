#include "main.h"

static void	init_param_arr(t_params *p)
{
	int			i;

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
}

static void	init_param(t_params *p, int argc, char **argv)
{
	if (ft_atoi(argv[1], &p->num_of_philo) == -1)
		error_exit(ERR_PARAM);
	if (ft_atoi(argv[2], &p->ttdie) == -1)
		error_exit(ERR_PARAM);
	if (ft_atoi(argv[3], &p->tteat) == -1)
		error_exit(ERR_PARAM);
	if (ft_atoi(argv[4], &p->ttsleep) == -1)
		error_exit(ERR_PARAM);
	p->num_of_times_each_philo_must_eat = -1;
	if (argc == 6
		&& ft_atoi(argv[5], &p->num_of_times_each_philo_must_eat) == -1)
		error_exit(ERR_PARAM);
	if (MAX_PHILOSOPHERS < p->num_of_philo)
		error_exit(ERR_MAX_PHILOSOPHERS);
	else if (p->num_of_philo < 1 || p->ttdie < 0 || INT_MAX < p->ttdie
		|| p->tteat < 0 || INT_MAX < p->tteat
		|| p->ttsleep < 0 || INT_MAX < p->ttsleep)
		error_exit(ERR_PARAM);
	init_param_arr(p);
}

int	main(int argc, char **argv)
{
	int				i;
	pthread_t		t[MAX_PHILOSOPHERS];
	t_params		p;

	if (argc < 5 || 6 < argc)
		print_usage_exit();
	init_param(&p, argc, argv);
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
