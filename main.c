/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:25:10 by ml-hote           #+#    #+#             */
/*   Updated: 2025/10/02 02:10:39 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		if (ft_parsing(&table, av) == -1)
		{
			if (table.philo_nbr == 0)
				ft_err_exit(R "WHO'S GONNA THINK FOR YOU ?" RESET);
			else if (table.philo_nbr > 200)
				ft_err_exit(R "TOO MUCH PHILOS !" RESET);
			ft_print_e_parsing(&table);
			return (1);
		}
		ft_init(&table);
		ft_start(&table);
		ft_cleaning(&table);
	}
	else
	{
		ft_err_exit(R "Wrong input" RESET ", Correct one is "
			G "./philo number_of_philosophers \
			time_to_die time_to_eat time_to_sleep"
			"[number_of_times_each_philosopher_must_eat]" RESET);
	}
	return (0);
}
