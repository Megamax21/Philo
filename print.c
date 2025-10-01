/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:37:59 by ml-hote           #+#    #+#             */
/*   Updated: 2025/10/02 00:54:13 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_dbg(t_philo *philo, const char *str)
{
	ft_smutex(&philo->table->print_mutex, LOCK);
	printf("%s\n", str);
	ft_smutex(&philo->table->print_mutex, UNLOCK);
}

void	ft_print_status(t_status status, t_philo *philo)
{
	long	passed;

	if (ft_get_int(&philo->stop_mtx, &philo->stop_everything))
		return ;
	if (philo->full == 1)
		return ;
	ft_smutex(&philo->table->t_mutex, LOCK);
	passed = ft_get_time(MILLI) - philo->table->start_simulation;
	if ((status == TAKEN_FORK_1 || status == TAKEN_FORK_2))
	{
		printf("%li %i has taken a fork\n", passed, philo->id);
	}
	else if (status == EATING)
		printf("%li %i is eating\n", passed, philo->id);
	else if (status == SLEEPING)
		printf("%li %i is sleeping\n", passed, philo->id);
	else if (status == THINKING)
		printf("%li %i is thinking\n", passed, philo->id);
	else if (status == DIED)
		printf(R "%li %i died\n" RESET, passed, philo->id);
	else
		print_dbg(philo, "No status");
	ft_smutex(&philo->table->t_mutex, UNLOCK);
}
