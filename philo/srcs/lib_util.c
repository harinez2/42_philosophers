/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libutil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 01:52:33 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/18 02:11:24 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1000 + (int)(tv.tv_usec / 1000));
}

void	usleep_exact(long time_in_usec)
{
	struct timeval	tv;
	long			start;
	long			end;

	gettimeofday(&tv, NULL);
	start = tv.tv_sec * 1000000 + tv.tv_usec;
	while (1)
	{
		usleep(200);
		gettimeofday(&tv, NULL);
		end = tv.tv_sec * 1000000 + tv.tv_usec;
		if ((end - start) >= time_in_usec)
			break ;
	}
}
