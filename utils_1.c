#include "philo.h"
void ft_wait4threads(t_table *table)
{
	while (!ft_get_bool(&table->t_mutex, &table->threads_ready))
		;
}

long	ft_get_time(t_timecode timecode)
{
	struct timeval timev;
	
	if (gettimeofday(&timev, NULL))
		ft_err_exit(R "GETTIMEOFDAY DIDN'T WORK !\n" RESET);
	if (timecode == SECONDS)
		return (timev.tv_sec + (timev.tv_usec / 1000000));
	else if (timecode == MILLI)
		return ((timev.tv_sec * 1000) + (timev.tv_usec / 1000));
	else if (timecode == MICRO)
		return ((timev.tv_sec * 1000000) + (timev.tv_usec));
	else
		ft_err_exit(R "WRONG INPUT IN GET TIME\n" RESET);
	return (0);
}

void	ft_precise_sleep(long useconds, t_table *table)
{
	long	start;
	long	passed;
	long	remain;

	start = ft_get_time(MICRO);
	while (ft_get_time(MICRO) - start < useconds)
	{
		if (ft_get_EOSimulation(table))
			break ;
		passed = ft_get_time(MICRO) - start;
		remain = useconds - passed;

		if (remain > 1000)
			usleep(remain / 2);
		else
		{
			while (ft_get_time(MICRO) - start < useconds)
				;
		}
	}
}
