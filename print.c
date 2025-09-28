#include "philo.h"

void	write_status_debug(t_status status, t_philo *philo, long passed)
{
	if ((status == TAKEN_FORK_1 || status == TAKEN_FORK_2)
		&& ft_get_EOSimulation(philo->table) == 0)
	{
		if (status == TAKEN_FORK_1)
			printf("%li %i 🍴 took the left fork\n", passed, philo->id);
		else
			printf("%li %i 🍴 took the right fork\n", passed, philo->id);
	}
	else if (status == EATING)
		printf("%li %i 🍝 is eating\n", passed, philo->id);
	else if (status == SLEEPING)
		printf("%li %i 😴 is sleeping\n", passed, philo->id);
	else if (status == THINKING)
		printf("%li %i 🤔 is thinking\n", passed, philo->id);
	else if (status == DIED && !ft_get_EOSimulation(philo->table))
	{
		printf(R "%li %i 💀 died\n" RESET, passed, philo->id);
		ft_set_bool(&philo->table->t_mutex, &philo->table->end_simulation, 1);
	}
}

void	ft_print_status(t_status status, t_philo *philo, int debug)
{
	long	passed;
	
	passed = ft_get_time(MILLI) - philo->table->start_simulation;
	
	if (philo->full == 1)
		return ;

	ft_smutex(&philo->table->t_mutex, LOCK);
	if (debug == 1)
		write_status_debug(status, philo, passed);
	if ((status == TAKEN_FORK_1 || status == TAKEN_FORK_2)
		&& ft_get_EOSimulation(philo->table) == 0)
		printf("%li %i has taken a fork\n", passed, philo->id);
	else if (status == EATING)
		printf("%li %i is eating\n", passed, philo->id);
	else if (status == SLEEPING)
		printf("%li %i is sleeping\n", passed, philo->id);
	else if (status == THINKING)
		printf("%li %i is thinking\n", passed, philo->id);
	else if (status == DIED && !ft_get_EOSimulation(philo->table))
	{
		printf(R "%li %i died\n" RESET, passed, philo->id);
		ft_set_bool(&philo->table->t_mutex, &philo->table->end_simulation, 1);
	}


	ft_smutex(&philo->table->t_mutex, UNLOCK);
}

