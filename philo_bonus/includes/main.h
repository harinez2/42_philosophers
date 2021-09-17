/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 01:52:42 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/18 02:36:06 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <semaphore.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>

# include "constants.h"
# include "structs.h"
# include "prototypes.h"

sem_t	*g_sem_philo;
sem_t	*g_sem_dead;

#endif
