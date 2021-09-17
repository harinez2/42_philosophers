#include "main.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1000 + (int)(tv.tv_usec / 1000));
}

void	usleep_exact(long time_in_usec)
{
	struct timeval	tv;
	long			start;
	long			end;

	gettimeofday(&tv, NULL);
	start = tv.tv_sec * 1000000 + tv.tv_usec;
	while (1)
	{
		usleep(200);
		gettimeofday(&tv, NULL);
		end = tv.tv_sec * 1000000 + tv.tv_usec;
		if ((end - start) >= time_in_usec)
			break ;
	}
}
