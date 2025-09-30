#include "philo.h"

static void ft_think(t_philo *philo)
{
	ft_print_status(THINKING, philo, DEBUG_MODE);
}

static void	ft_eat(t_philo *philo)
{

	if (philo->id % 2 == 1)
	{
		// ft_smutex(&philo->l_fork->fork, LOCK);
		// printf("philo %i take %p fork\n", philo->id, &philo->l_fork->fork_id);
		pthread_mutex_lock(&philo->l_fork->fork);

		// printf("philo %i take %p fork\n", philo->id, &philo->r_fork->fork_id);
		if (philo->r_fork == NULL)
			return ;
		pthread_mutex_lock(&philo->r_fork->fork);
		
		ft_print_status(TAKEN_FORK_1, philo, DEBUG_MODE);
		// ft_smutex(&philo->r_fork->fork, LOCK);
		ft_print_status(TAKEN_FORK_2, philo, DEBUG_MODE);
	}
	else
	{
		// printf("philo %i take %p fork\n", philo->id, &philo->r_fork->fork_id);
		pthread_mutex_lock(&philo->r_fork->fork);
		// printf("philo %i take %p fork\n", philo->id, &philo->l_fork->fork_id);
		pthread_mutex_lock(&philo->l_fork->fork);
		
		// ft_smutex(&philo->r_fork->fork, LOCK);
		// printf("philo %i take %p fork\n", philo->id, &philo->r_fork->fork_id);
		ft_print_status(TAKEN_FORK_2, philo, DEBUG_MODE);
		// ft_smutex(&philo->l_fork->fork, LOCK);
		// printf("philo %i take %p fork\n", philo->id, &philo->l_fork->fork_id);
		ft_print_status(TAKEN_FORK_1, philo, DEBUG_MODE);
		
	}
	ft_set_long(&philo->philo_mtx, &philo->last_meal_time, (ft_get_time(MILLI)));
	philo->meals_counter++;
	ft_print_status(EATING, philo, DEBUG_MODE);
	ft_precise_sleep(philo->table->time_to_eat, philo->table);
	// if (philo->table->nbr_limit_meals > 0 && philo->meals_counter >= philo->table->nbr_limit_meals)
	// 	ft_set_bool(&philo->philo_mtx, &philo->full, 1);

	pthread_mutex_unlock(&philo->r_fork->fork);
	pthread_mutex_unlock(&philo->l_fork->fork);
	// ft_smutex(&philo->r_fork->fork, UNLOCK);
	// ft_smutex(&philo->l_fork->fork, UNLOCK);

}

static void	ft_sleep(t_philo *philo)
{
	if (philo->meals_counter == 0)
		return ;
	ft_print_status(SLEEPING, philo, DEBUG_MODE);
	ft_precise_sleep(philo->table->time_to_sleep, philo->table);
}

void	ft_start(t_table *table)
{
	int	i;
	pthread_t monitor_thread;

	if (table->nbr_limit_meals == 0)
		return ;
	else
	{
		// Start monitor thread
		if (pthread_create(&monitor_thread, NULL, ft_monitor_simulation, table) != 0)
			ft_err_exit(R "MONITOR THREAD CREATION FAILED!\n" RESET);

		i = 0;
			while (i < table->philo_nbr) /* Creation of threads for each philo */
		{
			ft_sthread(&table->philos[i].thread_id, ft_sim, &table->philos[i], CREATE);
			i+=2;
		}
		i = 1;
		while (i < table->philo_nbr) /* Creation of threads for each philo */
		{
			ft_sthread(&table->philos[i].thread_id, ft_sim, &table->philos[i], CREATE);
			i+=2;
		}
	}
	table->start_simulation = ft_get_time(MILLI);
	ft_set_bool(&table->t_mutex, &table->threads_ready, 1);
	i = 0;
	printf(C "Philo nbr = %li\n" RESET, table->philo_nbr);
	while (i < table->philo_nbr)
	{
		ft_sthread(&table->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	pthread_join(monitor_thread, NULL);
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
		ft_think(philo);
		if (philo->last_meal_time != 0)
		{
			// printf(M"%li WHAT'S THE TIME ?\n"RESET, (ft_get_time(MILLI) - ft_get_long(&philo->philo_mtx, &philo->last_meal_time)));
			// printf("MMH ? %li\n", philo->table->time_to_die);
			// if ((ft_get_time(MILLI) - philo->last_meal_time) > philo->table->time_to_die)
			// 	ft_set_bool(&philo->philo_mtx, &philo->dead, 1);
		}
		ft_eat(philo);
		ft_sleep(philo);
		// ft_set_bool(&philo->table->t_mutex, &philo->table->end_simulation, 1);
	}
	return (NULL);
}
