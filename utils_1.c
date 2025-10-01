/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:36:19 by ml-hote           #+#    #+#             */
/*   Updated: 2025/10/02 00:52:55 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_wait4threads(t_table *table)
{
	while (!ft_get_int(&table->t_mutex, &table->threads_ready))
		;
}

long	ft_get_time(t_timecode timecode)
{
	struct timeval	timev;

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
		if (ft_get_eosimulation(table))
			break ;
		passed = ft_get_time(MICRO) - start;
		remain = useconds - passed;
		if (remain > 1000)
		{
			long nb_sleeps = (remain - 1000) / 100;
			long residue = (remain - 1000) % 100;
			int i = 0;

			while (ft_get_eosimulation(table) && i < nb_sleeps)
			{
				usleep(100);
				i++;
			}
			usleep(residue);
		}
		else
		{
			while (ft_get_eosimulation(table) && ft_get_time(MICRO) - start < useconds)
				;
		}
	}
}
