#include "philo.h"

void print_dbg(t_philo *philo, const char *str)
{
	ft_smutex(&philo->table->print_mutex, LOCK);
	printf("%s\n", str);
	ft_smutex(&philo->table->print_mutex, UNLOCK);
}

void	ft_print_status(t_status status, t_philo *philo)
{
	long	passed;

	// if (ft_get_EOSimulation(philo->table) == 0)
	// 	return;
	
	passed = ft_get_time(MILLI) - philo->table->start_simulation;
	if (philo->full == 1)
		return ;
	ft_smutex(&philo->table->t_mutex, LOCK); // lock mutex
	// char *print;
	// if (status == TAKEN_FORK_1)
	// 	print = strdup("TAKEN_FORK_1");
	// else if (status == TAKEN_FORK_2)
	// 	print = strdup("TAKEN_FORK_2");
	// else if (status == SLEEPING)
	// 	print = strdup("SLEEPING");
	// else if (status == EATING)
	// 	print = strdup("EATING");
	// else if (status == THINKING)
	// 	print = strdup("THINKING");
	// else if (status == DIED)
	// 	print = strdup("DIED");
	// else
	// {
	// 	print = calloc(sizeof(char), 2);
	// 	print[0] = status + '0';
	// 	print[1] = '\0';
	// }
	// print_dbg(philo, print);
	if ((status == TAKEN_FORK_1 || status == TAKEN_FORK_2)){
		printf("%li %i has taken a fork\n", passed, philo->id);
	}
	else if (status == EATING){
		printf("%li %i is eating\n", passed, philo->id);	
	}
	else if (status == SLEEPING){
		printf("%li %i is sleeping\n", passed, philo->id);
	}
	else if (status == THINKING){
		printf("%li %i is thinking\n", passed, philo->id);	
	}
	else if (status == DIED && !ft_get_EOSimulation(philo->table))
	{
		printf(R "%li %i died\n" RESET, passed, philo->id);
		ft_set_int(&philo->table->t_mutex, &philo->table->end_simulation, 1);
	}
	else {
		print_dbg(philo, "No status");
	}
	ft_smutex(&philo->table->t_mutex, UNLOCK);
}

