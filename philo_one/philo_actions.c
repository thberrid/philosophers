/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 11:13:54 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/21 11:14:06 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

void	eats(t_philo *self)
{
	ft_usleep(self->roomdata->tt_eat);
	pthread_mutex_unlock(&self->neighboor->fork);
	pthread_mutex_unlock(&self->fork);
}

void	sleeps(t_philo *self)
{
	ft_usleep(self->roomdata->tt_sleep);
}

void	takes_rightfork(t_philo *self)
{
	pthread_mutex_lock(&(self->neighboor->fork));
}

void	takes_leftfork(t_philo *self)
{
	pthread_mutex_lock(&(self->fork));
}

void	thinks(t_philo *self)
{
	(void)self;
}
