/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:35:44 by ml-hote           #+#    #+#             */
/*   Updated: 2025/10/01 19:35:45 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_err_exit(const char *err)
{
	printf("%s\n", err);
}

void	*ft_smalloc(size_t b)
{
	void	*ret;

	ret = malloc(b);
	if (ret == NULL)
		ft_err_exit(R "MALLOC HAS AN ERROR !\n" RESET);
	return (ret);
}

static void	ft_emutex(int state, t_lockstate lockstate) /* Mutex error handler*/
{
	if (state == 0)
		return ;
	if (state == EINVAL && (lockstate == LOCK
			|| lockstate == UNLOCK || lockstate == DESTROY))
		ft_err_exit(R "MUTEX HAS AN INVALID VALUE !\n" RESET);
	else if (state == EINVAL && lockstate == INIT)
		ft_err_exit(R "ATTR VALUE IS INVALID !\n" RESET);
	else if (state == EDEADLK)
		ft_err_exit(R "BEWARE OF THE DEADLOCK\n" RESET);
	else if (state == EPERM)
		ft_err_exit(R "NO HOLD A LOCK ON MUTEX\n" RESET);
	else if (state == ENOMEM)
		ft_err_exit(R "NOT ENOUGH MEMORY FOR ANOTHER MUTEX\n" RESET);
	else if (state == EBUSY)
		ft_err_exit(R "MUTEX IS LOCKED !\n" RESET);
}

void	ft_smutex(pthread_mutex_t *mutex, t_lockstate lockstate)
{
	if (lockstate == LOCK)
		ft_emutex(pthread_mutex_lock(mutex), lockstate);
	else if (lockstate == UNLOCK)
		ft_emutex(pthread_mutex_unlock(mutex), lockstate);
	else if (lockstate == INIT)
		ft_emutex(pthread_mutex_init(mutex, NULL), lockstate);
	else if (lockstate == DESTROY)
		ft_emutex(pthread_mutex_destroy(mutex), lockstate);
	else
		ft_err_exit(R "WRONG STATE OF ENUM\n");
}

void	ft_sthread(pthread_t *thread, void *(*foo)(void *),
	void *(data), t_lockstate lockstate) /* Safe Thread */
{
	if (lockstate == CREATE)
	{
		if (pthread_create(thread, NULL, foo, data) != 0)
			ft_err_exit(R "THREAD CREATION FAILED !\n" RESET);
	}
	else if (lockstate == JOIN)
	{
		if (pthread_join(*thread, NULL) != 0)
		{
			printf(R "NO GOD PLEASE NO\n" RESET);
			ft_err_exit(R "THREAD JOIN FAILED !\n" RESET);
		}
	}
	else if (lockstate == DETACH)
	{
		if (pthread_detach(*thread) != 0)
			ft_err_exit(R "THREAD DETACH FAILED !\n" RESET);
	}
	else
		ft_err_exit(R "WRONG STATE OF ENUM\n");
}
