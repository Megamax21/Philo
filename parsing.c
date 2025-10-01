#include "philo.h"

/*	Check NBR
	Checks if the string is a correct number that isn't higher than
	INT_MAX and that only has numeric values
*/
const char	*ft_check_nbr(const char *s)
{
	int			len;
	int			i;
	const char	*nb;
	i = 0;
	len = 0;
	
	while ((s[i] >= 9 && s[i] <= 13) || 32 == s[i])
		i++;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
		ft_err_exit(R "THERE'S A NEGATIVE VALUE IN THERE !\n" RESET);
	if (s[i] < '0' || s[i] > '9')
		ft_err_exit(R "INPUT IS NOT A NUMERIC VALUE !\n" RESET);
	nb = &s[i];
	while (s[i] >= '0' && s[i] <= '9')
	{
		i++;
		len++;
	}
	if (len > 10)
		ft_err_exit(R "VALUE IS BIGGER THAN INT_MAX !\n" RESET);
	return (nb);
}

/* Convert string to long */
long	ft_atol(const char *s)
{
	long	nbr;
	int		i;
	
	i = 0;
	nbr = 0;
	s = ft_check_nbr(s);
	while (s[i] >= '0' && s[i] <= '9')
	{
		nbr = (nbr * 10) + (s[i] - '0');
		i++;
	}
	
	if (nbr > INT_MAX)
		ft_err_exit(R "VALUE IS BIGGER THAN INT_MAX !\n" RESET);
	return (nbr);
}


void	ft_parsing(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (table->time_to_die < 60000
		|| table->time_to_sleep < 60000
		|| table->time_to_eat < 60000)
		ft_err_exit(R "VALUES MUST NOT BE UNDER 60 MS !\n" RESET);
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
	 	table->nbr_limit_meals = -1;
}
