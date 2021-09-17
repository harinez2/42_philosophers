/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:42:38 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/18 02:50:27 by yonishi          ###   ########.fr       */
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
// main.c
int			main(int argc, char **argv);
// philosopher.c
void		philosopher(t_param *p, int i);

#endif
