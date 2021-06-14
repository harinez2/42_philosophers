#include "main.h"

size_t	ft_strlen(const char *str)
{
	size_t		i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;

	i = 0;
	while (i + 1 < dstsize)
	{
		dst[i] = src[i];
		if (src[i] == '\0')
			break ;
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}
