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
		return (&philos[index + 1]);
	return (&philos[0]);
}

static int		philo_set(t_philo *philos, t_args *args, int index, int max)
{
	t_philo		*this_philo;

	this_philo = &(philos[index]);
	this_philo->id = index + 1;
	if (gettimeofday(&(this_philo->birth), NULL))
		return (1);
	if (gettimeofday(&((this_philo->state).last_change), NULL))
		return (1);
	this_philo->state.old = is_eating;
	this_philo->state.current = is_thinking;
	this_philo->tt_die = args->tt_die;
	this_philo->tt_eat = args->tt_eat;
	this_philo->tt_sleep = args->tt_sleep;
	this_philo->nb_meals = 0;
	this_philo->max_meals = args->max_meals;
	this_philo->neighboor = philo_find_neighboor(philos, index, max);
	if (pthread_mutex_init(&(this_philo->fork), NULL))
		return (1);
	return (0);
}

int	philos_alloc(t_philo **philos, t_args *args)
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
		if (philo_set(*philos, args, index, max))
			return (1);
		index += 1;
	}
	return (0);
}
