#include "philo.h"

// ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]


int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		ft_parsing(&table, av); // Checking the entries
		ft_init(&table); // Filling the table
		ft_start(&table);
		// ft_cleaning(&table);
	}
	else 
	{
		ft_err_exit(R "Wrong input" RESET ", Correct one is " 
			G "./philo number_of_philosophers time_to_die time_to_eat time_to_sleep"
			"[number_of_times_each_philosopher_must_eat]" RESET);
	}

	return (0);
}