#include "philo.h"

// Returns 1 if all philosophers are full, 0 otherwise
static int all_philos_full(t_table *table)
{
	int i;
	for (i = 0; i < table->philo_nbr; i++)
	{
		if (table->philos[i].full == 0)
			return 0;
	}
	return 1;
}

// Monitor thread function
void *ft_monitor_simulation(void *arg)
{
	t_table *table = (t_table *)arg;
	while (!ft_get_EOSimulation(table))
	{
		if (all_philos_full(table))
		{
			ft_set_bool(&table->t_mutex, &table->end_simulation, 1);
			break;
		}
		usleep(1000); // Sleep 1ms to avoid busy-waiting
	}
	return NULL;
}