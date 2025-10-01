#include "philo.h"
#include <stdlib.h>

void	ft_cleaning(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		// ft_smutex(&table->philos[i].philo_mtx, DESTROY);
		// ft_smutex(&table->philos[i].counter_mtx, DESTROY);
		// ft_smutex(&table->philos[i].r_fork->fork, DESTROY);
		// ft_smutex(&table->philos[i].l_fork->fork, DESTROY);
		free(&table->philos[i]);
	}
}