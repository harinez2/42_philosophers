/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 01:52:22 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/18 01:52:23 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

size_t	ft_strlen(const char *str)
{
	size_t		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putchars(char *s)
{
	write(1, s, ft_strlen(s));
}

void	print_num(long d)
{
	char	c;

	if (d < 0)
	{
		write(1, "-", 1);
		print_num(d / 10 * -1);
		print_num(d % 10 * -1);
		return ;
	}
	if (d >= 10)
		print_num(d / 10);
	c = d % 10 + '0';
	write(1, &c, 1);
}

int	ft_atoi(char *s, int *retnum)
{
	int	ret;
	int	i;
	int	neg;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\f' || s[i] == '\r' || s[i] == '\v')
		i++;
	neg = 1;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
	{
		neg = -neg;
		i++;
	}
	ret = 0;
	while (s[i] >= '0' && s[i] <= '9')
		ret = ret * 10 + s[i++] - '0';
	if (i == 0 || s[i] != '\0'
		|| (long)ret * (long)neg > INT_MAX || (long)ret * (long)neg < INT_MIN)
		return (-1);
	*retnum = ret * neg;
	return (0);
}
