/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:42:38 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/19 01:50:49 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

// error.c
void		error_exit(int errcode);
void		print_usage_exit(void);
// lib_ft.c
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
int			ft_atoi(char *s, int *retnum);
// lib_util.c
long		get_time(void);
void		usleep_exact(long time_in_usec);
// main.c
int			main(int argc, char **argv);
// philo.c
void		print_status(long time, int who, int something);
void		philosopher(t_param *p, int i);
// philo_chgstatus.c
int			change_status(t_param *p, t_phi *me);
// philo_wait.c
void		wait_all_philosophers(t_param *p);

#endif
