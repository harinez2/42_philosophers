#ifndef MAIN_H
# define MAIN_H

# include <semaphore.h>
# include <fcntl.h>
# include <stdlib.h>

# define RETRY_MAX		10

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
