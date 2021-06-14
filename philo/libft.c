#include "main.h"

int	ft_atoi(char *s, int *retnum)
{
	int	ret;
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\f' || s[i] == '\r' || s[i] == '\v')
		i++;
	if (s[i] == '+')
		i++;
	ret = 0;
	while (s[i] >= '0' && s[i] <= '9')
		ret = ret * 10 + s[i++] - '0';
	if (i == 0)
		return (-1);
	*retnum = ret;
	return (0);
}
