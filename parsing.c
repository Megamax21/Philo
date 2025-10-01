/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:24:07 by ml-hote           #+#    #+#             */
/*   Updated: 2025/10/02 00:59:10 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (s[i] == 32)
		i++;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
		return (R "THERE'S A NEGATIVE VALUE IN THERE !" RESET);
	if (s[i] < '0' || s[i] > '9')
		return (R "INPUT IS NOT A NUMERIC VALUE !" RESET);
	nb = &s[i];
	while (s[i] >= '0' && s[i] <= '9')
	{
		i++;
		len++;
	}
	if (s[i] != '\0')
		return (R "INPUT IS NOT A NUMERIC VALUE !" RESET);
	if (len > 10)
		return (R "VALUE IS BIGGER THAN INT_MAX !" RESET);
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
	if (s[0] < '0' || s[0] > '9')
	{
		ft_err_exit(s);
		return (-1);
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		nbr = (nbr * 10) + (s[i] - '0');
		i++;
	}
	if (nbr > INT_MAX)
	{
		ft_err_exit(R "VALUE IS BIGGER THAN INT_MAX !" RESET);
		return (-1);	
	}
	return (nbr);
}

int	ft_parsing(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (av[5])
	{
		table->nbr_limit_meals = ft_atol(av[5]);
		if (table->nbr_limit_meals < 0)
			return (-1);
	}
	else
		table->nbr_limit_meals = -1;
	if (table->philo_nbr < 0
		|| table->time_to_die < 0
		|| table->time_to_sleep < 0
		|| table->time_to_eat < 0)
		return (-1);
	if (table->time_to_die < 60
		|| table->time_to_sleep < 60000
		|| table->time_to_eat < 60000)
	{
		ft_err_exit(R "VALUES MUST NOT BE UNDER 60 MS !" RESET);
		return (-1);
	}
	return (0);
}
