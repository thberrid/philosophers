/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 11:03:06 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/21 11:03:14 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_two.h>

static t_philo	*philo_find_neighboor(t_philo *philos, int index, int max)
{
	if (index + 1 < max)
		return (&philos[index + 1]);
	return (&philos[0]);
}

static int		philo_set(t_philo *philos, t_roomdata *roomdata, int index)
{
	t_philo			*this;

	this = &(philos[index]);
	this->id = index + 1;
	this->state.id = is_thinking;
	this->meals.count = 0;
	this->neighboor = philo_find_neighboor(philos, index, roomdata->philos_len);
	this->roomdata = roomdata;
	if (pthread_mutex_init(&(this->fork.mutex), NULL))
		return (1);
	return (0);
}

static int		philos_alloc(t_philo **philos, t_roomdata *roomdata)
{
	int				index;
	int				philos_len;

	philos_len = roomdata->philos_len;
	if (!(*philos = (t_philo *)malloc(sizeof(t_philo) * philos_len)))
		return (1);
	index = 0;
	while (index < philos_len)
	{
		if (philo_set(*philos, roomdata, index))
		{
//			forksmutex_destroy(*philos, index - 1);
			free(*philos);
			return (1);
		}
		index += 1;
	}
	return (0);
}

static int		roomdata_set(t_roomdata *roomdata)
{
	/*
	if (pthread_mutex_init(&roomdata->printer.mutex, NULL))
		return (1);
	roomdata->printer.data = OPEN;
	*/
	sem_open(SEMNAME_FORKS, O_CREAT, roomdata->philos_len);
	sem_open(SEMNAME_PRINTER, O_CREAT, 1);
	roomdata->goaled = 0;
	return (0);
}

int				data_set
	(int ac, char **av, t_roomdata *roomdata, t_philo **philos)
{
	if (args_get(ac, av, roomdata))
	{
		return (write(1, "usage: nb_of_philos tt_die tt_eat \
tt_sleep [nb_of_meals]\n", 57));
	}
	if (roomdata_set(roomdata))
		return (write(1, "room mutex error\n", 17));
	if (philos_alloc(philos, roomdata))
		return (write(1, "init alloc error\n", 17));
	return (0);
}
