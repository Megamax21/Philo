#include "philo.h"

static void ft_think(t_philo *philo)
{
	ft_print_status(THINKING, philo, DEBUG_MODE);
}

static void	ft_eat(t_philo *philo)
{
	ft_smutex(&philo->l_fork->fork, LOCK);
	ft_print_status(TAKEN_FORK_1, philo, DEBUG_MODE);
	ft_smutex(&philo->r_fork->fork, LOCK);
	ft_print_status(TAKEN_FORK_2, philo, DEBUG_MODE);

	ft_set_long(&philo->philo_mtx, &philo->last_meal_time, ft_get_time(MILLI));
	philo->meals_counter++;
	ft_print_status(EATING, philo, DEBUG_MODE);
	ft_precise_sleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0 && philo->meals_counter >= philo->table->nbr_limit_meals)
		ft_set_bool(&philo->philo_mtx, &philo->full, 1);
	ft_smutex(&philo->r_fork->fork, UNLOCK);
	ft_smutex(&philo->l_fork->fork, UNLOCK);

}

void	ft_start(t_table *table)
{
	int	i;

	i = 0;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		; // TODO
	else
	{
		while (i < table->philo_nbr) /* Creation of threads for each philo */
		{
			ft_sthread(&table->philos[i].thread_id, ft_sim, &table->philos[i], CREATE);
			i++;
		}
	}

	table->start_simulation = ft_get_time(MILLI);
	
	ft_set_bool(&table->t_mutex, &table->threads_ready, 1);
	
	i = 0;
	while (i < table->philo_nbr)
	{
		ft_sthread(&table->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
}

void	*ft_sim(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_wait4threads(philo->table);

	while (ft_get_EOSimulation(philo->table) == 0)
	{
		if (philo->full == 1)
			break ;
		
		ft_eat(philo);

		ft_print_status(SLEEPING, philo, DEBUG_MODE);
		ft_precise_sleep(philo->table->time_to_sleep, philo->table);
		
		ft_think(philo);
	}

	return (NULL);
}