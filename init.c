/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:40:27 by ml-hote           #+#    #+#             */
/*   Updated: 2025/10/01 19:40:28 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>

static void	ft_philo_init(t_table *table)
{
	int		i;
	t_philo	*philos;

	i = 0;
	while (i < table->philo_nbr)
	{
		philos = table->philos + i;
		philos->id = i + 1;
		philos->meals_counter = 0;
		philos->full = 0;
		philos->table = table;
		philos->stop_everything = 0;
		philos->last_meal_time = ft_get_time(MILLI);
		ft_smutex(&philos->philo_mtx, INIT);
		ft_smutex(&philos->counter_mtx, INIT);
		ft_smutex(&philos->stop_mtx, INIT);
		philos->l_fork = &table->forks[i];
		if (table->philo_nbr == 1)
		{
			philos->r_fork = NULL;
			return ;
		}
		philos->r_fork = &table->forks[(i + 1) % table->philo_nbr];
		i++;
	}
}

void	ft_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = 0;
	table->philos = ft_smalloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = ft_smalloc(sizeof(t_fork) * table->philo_nbr);
	table->threads_ready = 0;
	ft_smutex(&table->t_mutex, INIT);
	ft_smutex(&table->print_mutex, INIT);
	while (i < table->philo_nbr)
	{
		ft_smutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
		i++;
	}
	ft_philo_init(table);
}
