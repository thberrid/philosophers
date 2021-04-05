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

#include <philo_two.h>

int	eats(t_philo *self)
{
	ft_usleep(self->roomdata->tt.eat);
	sem_post(&self->roomdata->forks_bunch);
	sem_post(&self->roomdata->forks_bunch);
	/*
	ft_usleep(self->roomdata->tt.eat);
	mutex_access(&self->fork, self, noctr, apply_fork_free);
	mutex_access(&self->neighboor->fork, self, noctr, apply_fork_free);
	*/
	return (0);
}

int	sleeps(t_philo *self)
{
	ft_usleep(self->roomdata->tt.sleep);
	return (0);
}

int	takes_rightfork(t_philo *self)
{
	sem_wait(&self->roomdata->forks_bunch);
	return (0);
	/*
	int			retrn;
	t_mtxdata	*right_fork;

	right_fork = &self->neighboor->fork;
	retrn = mutex_access(right_fork, self, ctr_is_open, apply_fork_take);
	return (retrn);
	*/
}

int	takes_leftfork(t_philo *self)
{
	sem_wait(&self->roomdata->forks_bunch);
	/*
	return (mutex_access(&self->fork, self, ctr_is_open, apply_fork_take));
	*/
}

int	thinks(t_philo *self)
{
	(void)self;
	return (0);
}
