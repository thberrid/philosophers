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

#include <philo_three.h>

void	clean(t_philo *philos, t_roomdata *roomdata)
{
	sem_close(roomdata->printer);
	sem_close(roomdata->forks_bunch);
	free(philos);
}
