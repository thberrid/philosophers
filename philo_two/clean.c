/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 21:00:43 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/14 21:00:45 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_two.h>

void	forksmutex_destroy(t_philo *philos, int len)
{
	int		index;

	index = 0;
	while (index < len)
	{
		pthread_mutex_destroy(&philos[index].fork.mutex);
		index += 1;
	}
}

void	threads_gather(t_philo *philos, int max)
{
	int		index;

	index = 0;
	while (index < max)
	{
		pthread_join(philos[index].thread, NULL);
		index += 1;
	}
}

void	clean(t_philo *philos, t_roomdata *roomdata)
{
	pthread_mutex_destroy(&roomdata->printer.mutex);
	free(philos);
}
