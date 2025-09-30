#include "philo.h"
#include <stddef.h>

// static void ft_putforks(t_philo *philo, t_fork *forks, int	pos)
// {
// 	int	n_philo;

// 	n_philo = philo->table->philo_nbr;

// 	philo->l_fork = &forks[pos];
// 	philo->r_fork = &forks[(pos + 1) % n_philo];
// 	if (philo->id % 2 == 0)
// 	{
// 		philo->r_fork = &forks[pos];
// 		philo->l_fork = &forks[(pos + 1) % n_philo];
// 	}
// }

static void	ft_philo_init(t_table *table)
{
	int	i;
	t_philo *philos;

	i = 0;
	while (i < table->philo_nbr)
	{
		philos = table->philos + i;
		philos->id = i + 1;
		philos->meals_counter = 0;
		philos->full = 0;
		philos->table = table;
		ft_smutex(&philos->philo_mtx, INIT);
		// ft_putforks(philos, table->forks, i);
		philos->l_fork = &table->forks[i];
		// printf("philo %i take %p fork\n", philos->id, &philos->l_fork->fork_id);
		if (table->philo_nbr == 1)
		{
			philos->r_fork = NULL;
			// printf("philo %i take %p fork\n", philos->id, &philos->r_fork->fork_id);
			return ;
		}
		philos->r_fork = &table->forks[(i + 1) % table->philo_nbr];
		// printf("philo %i take %p fork\n", philos->id, &philos->r_fork->fork_id);
		i++;
	}
}

void	ft_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = 0;
	table->dead_dude = -1;
	table->philos = ft_smalloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = ft_smalloc(sizeof(t_fork) * table->philo_nbr);
	table->threads_ready = 0;
	ft_smutex(&table->t_mutex, INIT);
	ft_smutex(&table->print_mutex, INIT);
	while (i < table->philo_nbr)
	{
		ft_smutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
		i++;
	}
	ft_philo_init(table);
}