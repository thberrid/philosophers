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

static int	is_dead(t_philo *self)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (self->meals.count == 0)
	{
		if (tv_to_ms(&now) - tv_to_ms(&self->roomdata->birth)
			>= self->roomdata->tt_die)
			return (1);
	}
	else
	{
		if (tv_to_ms(&now) - tv_to_ms(&self->meals.time)
			>= self->roomdata->tt_die)
			return (1);
	}
	return (0);
}

int			is_this_the_end(t_philo *self)
{
	if (self->roomdata->table.state == CLOSED)
		return (1);
	if (is_dead(self))
	{
		dies(self);
		return (1);
	}
	return (0);
}

static int	is_goal_achieved(t_philo *self)
{
	t_roomdata *roomdata;

	roomdata = self->roomdata;
	if (roomdata->max_meals > 0
		&& self->meals.count >= roomdata->max_meals)
		roomdata->goaled += 1;
	if (roomdata->goaled == roomdata->philos_len)
	{
		roomdata->table.state = CLOSED;
		return (1);
	}
	return (0);
}

void		threads_monitor(t_philo *philo, t_roomdata *roomdata)
{
	t_philo			*first;

	first = philo;
	while (philo)
	{
		if (is_this_the_end(philo))
			break ;
		if (is_goal_achieved(philo))
			break ;
		philo = philo->neighboor;
		if (philo == first)
			roomdata->goaled = 0;
	}
}

int			threads_launch(t_philo *philos, t_roomdata *roomdata)
{
	int				index;
	int				max;

	gettimeofday(&roomdata->birth, NULL);
	index = 0;
	max = roomdata->philos_len;
	roomdata->table.state = OPEN;
	while (index < max)
	{
		if (pthread_create(&(philos[index].thread),
			NULL, &routine, &philos[index]))
		{
			roomdata->table.state = CLOSED;
			threads_gather(philos, index);
			forksmutex_destroy(philos, max);
			clean(philos, roomdata);
			return (1);
		}
		index += 1;
	}
	return (0);
}
