/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:42:41 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/23 15:49:32 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_param
{
	int		num_of_philo;
	int		ttdie;
	int		tteat;
	int		ttsleep;
	int		times_must_eat;
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
