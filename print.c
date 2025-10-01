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

    // Check philosopher's own stop flag
    if (ft_get_int(&philo->stop_mtx, &philo->stop_everything))
        return;

    passed = ft_get_time(MILLI) - philo->table->start_simulation;
    if (philo->full == 1)
        return ;
    ft_smutex(&philo->table->t_mutex, LOCK); // lock mutex

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
    else if (status == DIED)//  && !ft_get_EOSimulation(philo->table))
    {
        printf(R "%li %i died\n" RESET, passed, philo->id);
    }
    else {
        print_dbg(philo, "No status");
    }
    ft_smutex(&philo->table->t_mutex, UNLOCK);
}

