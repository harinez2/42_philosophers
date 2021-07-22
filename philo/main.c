#include "main.h"

static void	init_param(t_status *s)
{
	int			i;

	s->start_time = get_time();
	i = 0;
	while (i < s->param.num_of_philo)
	{
		s->ph[i].i = i;
		s->ph[i].lasteat_time = s->start_time;
		s->ph[i].status = P_THINKING;
		if (s->param.times_must_eat == -1)
			s->ph[i].remain_eat_time = 0;
		else
			s->ph[i].remain_eat_time = s->param.times_must_eat;
		s->fork[i].i = 1;
		i++;
	}
	s->someone_dead = 0;
	pthread_mutex_init(&s->mtx, NULL);
}

static void	read_param(t_param *p, int argc, char **argv)
{
	if (ft_atoi(argv[1], &p->num_of_philo) == -1)
		error_exit(ERR_PARAM);
	if (ft_atoi(argv[2], &p->ttdie) == -1)
		error_exit(ERR_PARAM);
	if (ft_atoi(argv[3], &p->tteat) == -1)
		error_exit(ERR_PARAM);
	if (ft_atoi(argv[4], &p->ttsleep) == -1)
		error_exit(ERR_PARAM);
	p->times_must_eat = -1;
	if (argc == 6
		&& ft_atoi(argv[5], &p->times_must_eat) == -1)
		error_exit(ERR_PARAM);
	if (MAX_PHILOSOPHERS < p->num_of_philo)
		error_exit(ERR_MAX_PHILOSOPHERS);
	else if (p->num_of_philo < 1 || p->ttdie < 0 || INT_MAX < p->ttdie
		|| p->tteat < 0 || INT_MAX < p->tteat
		|| p->ttsleep < 0 || INT_MAX < p->ttsleep)
		error_exit(ERR_PARAM);
}

int	main(int argc, char **argv)
{
	int				i;
	pthread_t		t[MAX_PHILOSOPHERS];
	t_status		s;

	if (argc < 5 || 6 < argc)
		print_usage_exit();
	read_param(&s.param, argc, argv);
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
	pthread_mutex_destroy(&s.mtx);
	return (0);
}
