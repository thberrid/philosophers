/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:38:15 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/11 16:38:16 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

static t_philo	*philo_find_neighboor(t_philo *philos, int index, int max)
{
	if (index + 1 < max)
		return (philos[index + 1]);
	return (philos[0]);
}

static int		philo_set(t_phi *philos, int index, int max)
{
	t_philo		*philo_this;

	this_philo = philos[index];
	this_philo->id = index;
	if (gettimeofday(this_philo->birth, NULL))
		return (1);
	this_philo->neighboor = philo_find_neighboor(philos, index, max);
	this_philo->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!this_philo->fork)
		return (1);
	memset(this_philo->fork, 0, sizeof(pthread_mutex_t));
	if (pthread_mutex_init(this_philo->fork, NULL))
		return (1);
	return (0);
}

int	philos_alloc(t_phi **philos, t_args *args)
{
	int		index;
	int		max;

	max = args->p_len;
	*philos = (t_philo *)malloc(sizeof(t_philo) * max);
	if (!*philos)
		return (1);
	index = 0;
	while (index < max)
	{
		if (philo_set(philos, index, max))
			return (1);
		index += 1;
	}
	return (0);
}
