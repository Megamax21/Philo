#include "philo.h"
#include <stddef.h>

void	ft_init(t_table *table)
{
	table->end_simulation = 0;
	table->philos = ft_smalloc(table->philo_nbr);
}