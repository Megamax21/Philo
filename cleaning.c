#include "philo.h"
#include <stdlib.h>

void	ft_cleaning(t_table *table)
{
	int	i;

	// Destroy mutexes in philos/forks
	for (i = 0; i < table->philo_nbr; i++)
	{
		pthread_mutex_destroy(&table->philos[i].philo_mtx);
		pthread_mutex_destroy(&table->philos[i].counter_mtx);
		pthread_mutex_destroy(&table->forks[i].fork);
	}
	pthread_mutex_destroy(&table->t_mutex);
	pthread_mutex_destroy(&table->print_mutex);

	// Free the arrays
	free(table->philos);
	free(table->forks);
}