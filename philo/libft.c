#include "main.h"

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
