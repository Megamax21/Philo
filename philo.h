/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 09:53:14 by ml-hote           #+#    #+#             */
/*   Updated: 2025/09/25 18:34:50 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>
// ANSI escape codes for bold color fonts in printf
// Usage: printf(R "This is bold red text." RESET);
#define BLACK	"\033[1;30m"
#define R		"\033[1;31m"
#define G		"\033[1;32m"
#define Y		"\033[1;33m"
#define B		"\033[1;34m"
#define M		"\033[1;35m"
#define C		"\033[1;36m"
#define W		"\033[1;37m"
#define RESET	"\033[0m"

/*	What we'll do ?
struct for the philos and the forks (mutexes)
struct for a table that will stock all of the infos
*/


typedef struct	s_fork
{
	pthread_mutex_t fork;
	int				fork_id;
}					t_fork;

typedef struct	s_philo
{
	int	id;
	long		meals_counter;
	int			full; // Will be a bool
	long		last_meal_time;
	/* Time since last meal will help 
		knowing if the philosopher is
		dead (if he has not eaten in
		a long time)
	*/
	t_fork		*l_fork;
	t_fork		*r_fork;
	pthread_t	thread_id;
}				t_philo;

typedef struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals; // optionnal arg. FLAG if -1
	long	start_simulation;
	int		end_simulation; // bool for when philo dies or all of them are full
	t_fork	*forks;
	t_philo	*philos;
}			t_table;

typedef enum e_lockstate
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}		t_lockstate;

void	ft_err_exit(const char *err);
void	ft_parsing(t_table *table, char **av);
void	*ft_smalloc (size_t b);

