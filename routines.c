/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:29:19 by ml-hote           #+#    #+#             */
/*   Updated: 2025/10/02 00:31:03 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think(t_philo *philo)
{
	if (ft_get_int(&philo->stop_mtx, &philo->stop_everything))
		return ;
	ft_print_status(THINKING, philo);
}

static int	ft_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->l_fork->fork);
		ft_print_status(TAKEN_FORK_1, philo);
		if (philo->r_fork == NULL)
		{
			ft_precise_sleep((philo->table->time_to_die + 3) * 1001,
				philo->table);
			pthread_mutex_unlock(&philo->l_fork->fork);
			return (1);
		}
		pthread_mutex_lock(&philo->r_fork->fork);
		ft_print_status(TAKEN_FORK_2, philo);
	}
	else
	{
		pthread_mutex_lock(&philo->r_fork->fork);
		ft_print_status(TAKEN_FORK_2, philo);
		pthread_mutex_lock(&philo->l_fork->fork);
		ft_print_status(TAKEN_FORK_1, philo);
	}
	return (0);
}

void	ft_eat(t_philo *philo)
{
	if (ft_fork(philo) == 1)
		return ;
	ft_print_status(EATING, philo);
	ft_set_long(&philo->philo_mtx, &philo->last_meal_time,
		(ft_get_time(MILLI)));
	ft_precise_sleep(philo->table->time_to_eat, philo->table);
	ft_smutex(&philo->counter_mtx, LOCK);
	philo->meals_counter++;
	ft_smutex(&philo->counter_mtx, UNLOCK);
	pthread_mutex_unlock(&philo->r_fork->fork);
	pthread_mutex_unlock(&philo->l_fork->fork);
}

void	ft_sleep(t_philo *philo)
{
	if (ft_get_int(&philo->stop_mtx, &philo->stop_everything))
	{
		return ;
	}
	ft_print_status(SLEEPING, philo);
	ft_precise_sleep(philo->table->time_to_sleep, philo->table);
}
