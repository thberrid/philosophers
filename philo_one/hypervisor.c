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

void	threads_monitor(t_philo *philo, t_roomdata *roomdata)
{
	int				goaled;
	t_philo			*first;

	first = philo;
	goaled = 0;
	while (philo)
	{
		
		if (roomdata->table.state == CLOSED)
			return ;
		
		if (is_dead(philo))
		{
			dies(philo);
			return ;
		}
		if (roomdata->max_meals > 0 
			&& philo->meals.count >= roomdata->max_meals)
			goaled += 1;
		if (goaled == roomdata->philos_len)
		{
			roomdata->table.state = CLOSED;
			return ;
		}
		philo = philo->neighboor;
		if (philo == first)
			goaled = 0;
	}
}

static void	birth_set(struct timeval *birth, t_philo *this)
{
	this->birth.tv_sec = birth->tv_sec;
	this->birth.tv_usec = birth->tv_usec;
	this->meals.time.tv_sec = birth->tv_sec;
	this->meals.time.tv_usec = birth->tv_usec;
}

int		threads_launch(t_philo	*philos, t_roomdata *roomdata)
{
	int				index;
	struct timeval	birth;
	int				max;

	gettimeofday(&birth, NULL);
	index = 0;
	max = roomdata->philos_len;
	roomdata->table.state = OPEN;
	while (index < max)
	{
	//	if (philos[index].id % 2)
//			usleep(50);
		birth_set(&birth, &philos[index]);
		if (pthread_create(&(philos[index].thread), NULL, &routine, &philos[index]))
		{
			roomdata->table.state = CLOSED;
			threads_gather(philos, index);
			forksmutex_destroy(philos, max);
			roomdatamutex_destroy(roomdata);
			free(philos);
			return (1);
		}
		index += 1;
	}
	return (0);
}