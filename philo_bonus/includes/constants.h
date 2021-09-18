/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:42:30 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/18 21:15:30 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define	MAX_PHILOSOPHERS	200
# define	P_TAKEN_FORK		1
# define	P_EATING			2
# define	P_SLEEPING			3
# define	P_THINKING			4
# define	P_DIED				5

# define	ST_PHILO_DEAD		1
# define	ST_SIMUL_FINISHED	2

# define	ERR_PARAM				-1
# define	ERR_MAX_PHILOSOPHERS	-2
# define	ERR_SEM_OPEN			-3
# define	ERR_SEM_CLOSE			-4
# define	ERR_SEM_WAIT			-5
# define	ERR_FAILED_TO_FORK		-6
# define	ERR_FAILED_TO_WAIT		-7

# define	SEM_OPEN_RETRY_MAX	10
# define	DBG					0

#endif
