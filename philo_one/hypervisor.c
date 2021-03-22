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
