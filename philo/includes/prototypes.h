/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:42:38 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/19 01:46:30 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

// error.c
int			print_error(int errcode);
// lib_ft.c
size_t		ft_strlen(const char *str);
void		ft_putchars(char *s);
void		print_num(long d);
int			ft_atoi(char *s, int *retnum);
// lib_util.c
long		get_time(void);
void		usleep_exact(long time_in_usec);
// main.c
int			main(int argc, char **argv);
// philo.c
void		print_status(long time, int who, int something);
void		*philosopher(void *arg);
// philo_chgstatus.c
int			change_status(t_status *s, int i);

#endif
