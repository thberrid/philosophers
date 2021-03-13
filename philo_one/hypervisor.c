/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hypervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:01:45 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/12 16:01:57 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>


void	table_close(t_args *args)
{
	pthread_mutex_lock(args->table_mutex);
	args->table[0] = CLOSED;
	pthread_mutex_unlock(args->table_mutex);
}

int		is_table_closed(t_args *args)
{
	int		retrn;

	retrn = OPEN;
	pthread_mutex_lock(args->table_mutex);
	retrn = args->table[0];
	pthread_mutex_unlock(args->table_mutex);
	return (retrn);
}

void	hypervision(t_philo *philo, t_args *args)
{
	int				goaled;
//	struct timeval	now;
	t_philo			*first;
	int 			philo_len;

	first = philo;
	goaled = 0;
	philo_len = args->p_len;
	while (philo)
	{
		if (is_table_closed(args) == CLOSED)
			return ;
		if (philo->meals.max > 0 && philo->meals.count >= philo->meals.max)
			goaled += 1;
		if (goaled == philo_len)
		{
			table_close(args);
			return ;
		}
		philo = philo->neighboor;
		if (philo == first)
			goaled = 0;
	}
}

void	launch_routines(t_philo	*philos, int max)
{
	int				index;
	struct timeval	birth;

	settimeofday(&birth, NULL);
	index = 0;
	while (index < max)
	{
		ft_memcpy(&(philos[index].birth), &birth, sizeof(struct timeval));
		ft_memcpy(&(philos[index].meals.last), &birth, sizeof(struct timeval));
		pthread_create(&(philos[index].thread), NULL, &routine, &philos[index]);
//		pthread_detach(philos[index].thread);
		index += 1;
	}
}

void	kill_and_collect(t_philo *philos, int max)
{
	int		index;
	t_philo	this;

	index = 0;
	while (index < max)
	{
		this = philos[index];
		pthread_join(this.thread, NULL);
		index += 1;
	}
}

void	clean(t_philo *philos, t_args *args)
{
	int		index;
	t_philo	this;
	int		max;

	index = 0;
	free(args->table);
	pthread_mutex_destroy(args->table_mutex);
	free(args->table_mutex);
	max = args->p_len;
	while (index < max)
	{
		this = philos[index];
		pthread_mutex_destroy(&(this.fork));
		index += 1;
	}
	free(philos);
}