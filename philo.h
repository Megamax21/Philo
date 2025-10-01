/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 09:53:14 by ml-hote           #+#    #+#             */
/*   Updated: 2025/10/01 06:07:02 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>

#include <string.h>
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

/* Structs */
typedef struct	s_fork
{
    pthread_mutex_t	fork;
    int				fork_id;
}					t_fork;

typedef struct s_table t_table;

typedef struct	s_philo
{
    int				id;
    int             dead;
    long			meals_counter;
    int				full;
    long			last_meal_time;
    int             stop_everything;
    t_fork			*l_fork;
    t_fork			*r_fork;
    pthread_t		thread_id;
    t_table			*table;
	pthread_mutex_t	philo_mtx;
    pthread_mutex_t stop_mtx;
    pthread_mutex_t counter_mtx;
}				t_philo;

typedef struct	s_table
{
    long			philo_nbr;
    long			time_to_die;
    long			time_to_eat;
    long			time_to_sleep;
    long			nbr_limit_meals;
    long			start_simulation;
    int				end_simulation;
    int             dead_dude;
    int				threads_ready;
    t_fork			*forks;
    t_philo			*philos;
    pthread_mutex_t	print_mutex;
    pthread_mutex_t	t_mutex;
}			t_table;

typedef enum	e_lockstate
{
    LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    CREATE,
    JOIN,
    DETACH,
}		t_lockstate;

typedef enum	e_timecode
{
	SECONDS,
	MILLI,
	MICRO,
}		t_timecode;

typedef enum	e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKEN_FORK_1,
	TAKEN_FORK_2,
	DIED,
}		t_status;

/* Error Handling */
void		ft_err_exit(const char *err);

/* Memory Handling */
void		*ft_smalloc(size_t b);

/* Mutex Handling */
void		ft_smutex(pthread_mutex_t *mutex, t_lockstate lockstate);

/* Thread Handling */
void		ft_sthread(pthread_t *thread, void *(*foo)(void *), void *data, t_lockstate lockstate);

/* Parsing & Conversion */
const char	*ft_check_nbr(const char *s);
long		ft_atol(const char *s);
void		ft_parsing(t_table *table, char **av);

/* Initialization */
void		ft_init(t_table *table);

/* Gets and sets*/
void		ft_set_int(pthread_mutex_t *mutex, int *dest, int value);
void		ft_set_long(pthread_mutex_t *mutex, long *dest, long value);
int			ft_get_int(pthread_mutex_t *mutex, int *val);
long		ft_get_long(pthread_mutex_t *mutex, long *val);
int			ft_get_EOSimulation(t_table *table);
long		ft_get_time(t_timecode timecode);
void		*ft_monitor_simulation(void *arg);
void		ft_precise_sleep(long useconds, t_table *table);
void		ft_wait4threads(t_table *table);
void		ft_print_status(t_status status, t_philo *philo);
void		print_dbg(t_philo *philo, const char *str);
void		ft_start(t_table *table);
void		*ft_sim(void *data);
void    	ft_cleaning(t_table *table);
