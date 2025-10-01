#include "philo.h"

static void ft_think(t_philo *philo)
{
    if (ft_get_int(&philo->stop_mtx, &philo->stop_everything))
        return;
    ft_print_status(THINKING, philo);
}

static void	ft_eat(t_philo *philo)
{
    if (ft_get_int(&philo->stop_mtx, &philo->stop_everything))
		return;

	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->l_fork->fork);
		if (philo->r_fork == NULL)
			return ;
		pthread_mutex_lock(&philo->r_fork->fork);
		ft_print_status(TAKEN_FORK_1, philo);
		ft_print_status(TAKEN_FORK_2, philo);
	}
	else
	{
		pthread_mutex_lock(&philo->r_fork->fork);
		pthread_mutex_lock(&philo->l_fork->fork);
		ft_print_status(TAKEN_FORK_2, philo);
		ft_print_status(TAKEN_FORK_1, philo);
	}
	ft_print_status(EATING, philo);
	ft_precise_sleep(philo->table->time_to_eat, philo->table);
	ft_set_long(&philo->philo_mtx, &philo->last_meal_time, (ft_get_time(MICRO)));
	ft_smutex(&philo->counter_mtx, LOCK);
	philo->meals_counter++;
	ft_smutex(&philo->counter_mtx, UNLOCK);
	if (ft_get_long(&philo->table->t_mutex, &philo->table->nbr_limit_meals) != -1)
	{
		if (ft_get_long(&philo->counter_mtx, &philo->meals_counter) >= ft_get_long(&philo->table->t_mutex, &philo->table->nbr_limit_meals))
			ft_set_int(&philo->counter_mtx, &philo->full, 1);
	}
	pthread_mutex_unlock(&philo->r_fork->fork);
	pthread_mutex_unlock(&philo->l_fork->fork);
}

static void	ft_sleep(t_philo *philo)
{
	if (ft_get_int(&philo->stop_mtx, &philo->stop_everything))
	{
		return ;
	}
	if (philo->meals_counter == 0)
	{
		return ;
	}
	ft_print_status(SLEEPING, philo);
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
		if (pthread_create(&monitor_thread, NULL, ft_monitor_simulation, table) != 0)
			ft_err_exit(R "MONITOR THREAD CREATION FAILED!\n" RESET);
		i = 0;
			while (i < table->philo_nbr)
		{
			ft_sthread(&table->philos[i].thread_id, ft_sim, &table->philos[i], CREATE);
			i+=2;
		}
		i = 1;
		while (i < table->philo_nbr) 
		{
			ft_sthread(&table->philos[i].thread_id, ft_sim, &table->philos[i], CREATE);
			i+=2;
		}
	}
	table->start_simulation = ft_get_time(MILLI);
	ft_set_int(&table->t_mutex, &table->threads_ready, 1);
	i = 0;
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
    while (!ft_get_int(&philo->stop_mtx, &philo->stop_everything))
    {
        ft_think(philo);
        ft_eat(philo);
        ft_sleep(philo);
    }
    return (NULL);
}
