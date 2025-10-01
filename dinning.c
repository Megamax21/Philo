/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:20:50 by ml-hote           #+#    #+#             */
/*   Updated: 2025/10/01 19:29:50 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	launch_simulation(t_table *table)
{
	int			i;

	i = 0;
	while (i < table->philo_nbr)
	{
		ft_sthread(&table->philos[i].thread_id, ft_sim,
			&table->philos[i], CREATE);
		i += 2;
	}
	i = 1;
	while (i < table->philo_nbr)
	{
		ft_sthread(&table->philos[i].thread_id,
			ft_sim, &table->philos[i], CREATE);
		i += 2;
	}
}

void	ft_start(t_table *table)
{
	int			i;
	pthread_t	monitor_thread;

	if (table->nbr_limit_meals == 0)
		return ;
	else
	{
		if (pthread_create(&monitor_thread, NULL,
				ft_monitor_simulation, table) != 0)
			ft_err_exit(R "MONITOR THREAD CREATION FAILED!" RESET);
		launch_simulation(table);
	}
	table->start_simulation = ft_get_time(MILLI);
	ft_set_int(&table->t_mutex, &table->threads_ready, 1);
	i = 0;
	while (i < table->philo_nbr)
		ft_sthread(&table->philos[i++].thread_id, NULL, NULL, JOIN);
	pthread_join(monitor_thread, NULL);
}

void	*ft_sim(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_wait4threads(philo->table);
	while (!ft_get_int(&philo->stop_mtx, &philo->stop_everything))
	{
		ft_think(philo);
		if (ft_get_int(&philo->stop_mtx, &philo->stop_everything))
			break ;
		ft_eat(philo);
		if (ft_get_int(&philo->stop_mtx, &philo->stop_everything))
			break ;
		ft_sleep(philo);
		if (ft_get_int(&philo->stop_mtx, &philo->stop_everything))
			break ;
	}
	return (NULL);
}
