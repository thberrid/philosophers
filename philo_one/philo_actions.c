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

int		mutex_access(t_mtx *obj, int (*ctr)(char), int (*apply)(char, char), char val)
{
	int		retrn;

	pthread_mutex_lock(obj->mutex);
	retrn = ctr(obj->val);
	if (retrn)
		apply(obj, val);
	pthread_mutex_unlock(obj->mutex);
	return (retrn);
}

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
	pthread_mutex_lock(&(self->fork.mutex));
	if (self->fork.data == FREE)
	{
		self->fork.data = self->id;
		self->state.id = has_taken_a_fork;
		gettimeofday(&self->state.time, NULL);
		state_print(self);
	}
	pthread_mutex_lock(&(self->neighboor->fork));
}

void	thinks(t_philo *self)
{
	(void)self;
}
