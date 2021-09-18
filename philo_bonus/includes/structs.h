/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:42:41 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/18 15:21:39 by yonishi          ###   ########.fr       */
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

typedef struct s_phi
{
	int			i;
	long		lasteat_time;
	long		now_time;
	int			status;
	long		eat_cnt;
}	t_phi;

#endif
