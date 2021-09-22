/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:42:41 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/23 01:00:45 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_param
{
	long		num_of_philo;
	long		ttdie;
	long		tteat;
	long		ttsleep;
	long		times_must_eat;
}	t_param;

typedef struct s_fork
{
	int				i;
	pthread_mutex_t	mtx;
}	t_fork;

typedef struct s_phi
{
	int			i;
	long		seq_start_time;
	long		lasteat_time;
	long		now_time;
	int			status;
	long		eat_cnt;
}	t_phi;

typedef struct s_status
{
	long			start_time;
	t_fork			fork[MAX_PHILOSOPHERS];
	int				someone_dead;
	long			dead_time;
	int				num_of_philo_ate;
	t_phi			ph[MAX_PHILOSOPHERS];
	t_param			param;
	int				tmp_i;
	pthread_mutex_t	mtx;
}	t_status;

#endif
