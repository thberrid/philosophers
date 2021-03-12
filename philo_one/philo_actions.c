/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:39:34 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/11 16:39:50 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

static int	philo_eats(t_philo *self)
{
	self->state.old = self->state.current;
	self->state.current = is_eating;
	self->meals.count += 1;
	gettimeofday(&self->state.last_change, NULL);
	gettimeofday(&self->meals.last, NULL);
	usleep(self->tt_eat);
	pthread_mutex_unlock(&(self->neighboor->fork));
	pthread_mutex_unlock(&(self->fork));
	return (0);
}

static int	philo_sleeps(t_philo *self)
{
	self->state.old = self->state.current;
	self->state.current = is_sleeping;
	gettimeofday(&self->state.last_change, NULL);
	usleep(self->tt_sleep);
	return (0);
}

static int	philo_thinks(t_philo *self)
{
	self->state.old = self->state.current;
	self->state.current = is_thinking;
	gettimeofday(&self->state.last_change, NULL);
	pthread_mutex_lock(&(self->neighboor->fork));
	pthread_mutex_lock(&(self->fork));
	return (0);
}

void	*routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (philo->meals.max >= 0 && philo->meals.count < philo->meals.max)
			philo_thinks(philo);
		else
			return (philo);
		philo_eats(philo);
		philo_sleeps(philo);
	}
	return (philo);
}