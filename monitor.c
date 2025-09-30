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

int	ft_death_check(t_table *table)
{
	int	i;
	long time_since_last_meal;

	time_since_last_meal = 0;
	i = 0;
	while (i < table->philo_nbr)
	{
		time_since_last_meal = (ft_get_time(MILLI) - ft_get_long(&table->philos[i].philo_mtx, 
			&table->philos[i].last_meal_time));
		if (time_since_last_meal > table->time_to_die)
		{
			table->end_simulation = 1;
			table->dead_dude = i;
		}
		i++;
	}

	return (0);
}
// Monitor thread function
void *ft_monitor_simulation(void *arg)
{
	t_table *table;
	table = (t_table *)arg;
	while (!ft_get_EOSimulation(table))
	{
		if (all_philos_full(table))
		{
			ft_set_bool(&table->t_mutex, &table->end_simulation, 1);
			break;
		}
		if (ft_death_check(table) == 1)
			exit(1);
		usleep(1000); 
	}
	return NULL;
}