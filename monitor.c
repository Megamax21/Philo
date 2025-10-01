/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:39:21 by ml-hote           #+#    #+#             */
/*   Updated: 2025/10/02 01:36:41 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_all_philos_stop(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		ft_set_int(&table->philos[i].stop_mtx,
			&table->philos[i].stop_everything, 1);
		i++;
	}
}

int	ft_death_check(t_table *table)
{
	int		i;
	long	time_since_last_meal;

	time_since_last_meal = 0;
	i = 0;
	while (i < table->philo_nbr)
	{
		time_since_last_meal = (ft_get_time(MILLI)
				- ft_get_long(&table->philos[i].philo_mtx,
					&table->philos[i].last_meal_time));
		if (time_since_last_meal > (table->time_to_die) + 3)
		{
			ft_print_status(DIED, &table->philos[i]);
			set_all_philos_stop(table);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_full_check(t_table *table)
{
	int	i;

	i = 0;
	if (table->nbr_limit_meals == -1)
		return (-1);
	while (i < table->philo_nbr)
	{
		if (ft_get_long(&table->philos[i].counter_mtx,
				&table->philos[i].meals_counter) < table->nbr_limit_meals)
			return (0);
		i++;
	}
	return (1);
}

void	*ft_monitor_simulation(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!ft_get_eosimulation(table))
	{
		if (ft_full_check(table) == 1)
		{
			ft_set_int(&table->t_mutex, &table->end_simulation, 1);
			set_all_philos_stop(table);
			printf(G "All philosophers ate at least %ld meals\n" RESET, table->nbr_limit_meals);
			break ;
		}
		if (ft_death_check(table) == 1)
		{
			ft_set_int(&table->t_mutex, &table->end_simulation, 1);
			printf(R "AYOOOOOOOOO\n" RESET);
			break ;
		}
	}
	return (NULL);
}
