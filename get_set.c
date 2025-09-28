#include "philo.h"

void	ft_set_bool(pthread_mutex_t *mutex, int *dest, int value)
{
	ft_smutex(mutex, LOCK);
	*dest = value;
	ft_smutex(mutex, UNLOCK);
}

int	ft_get_bool(pthread_mutex_t *mutex, int *val)
{
	int	ret;

	ft_smutex(mutex, LOCK);
	ret = *val;
	ft_smutex(mutex, UNLOCK);
	return(ret);
}

void	ft_set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	ft_smutex(mutex, LOCK);
	*dest = value;
	ft_smutex(mutex, UNLOCK);
}

int	ft_get_long(pthread_mutex_t *mutex, long *val)
{
	long	ret;

	ft_smutex(mutex, LOCK);
	ret = *val;
	ft_smutex(mutex, UNLOCK);
	return(ret);
}

int	ft_get_EOSimulation(t_table *table)
{
	return(ft_get_bool(&table->t_mutex, &table->end_simulation));
}