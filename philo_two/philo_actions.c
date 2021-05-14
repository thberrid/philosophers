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
	sem_post(self->roomdata->forks_bunch);
	sem_post(self->roomdata->forks_bunch);
	return (0);
}

int	sleeps(t_philo *self)
{
	ft_usleep(self->roomdata->tt.sleep);
	return (0);
}

int	takes_rightfork(t_philo *self)
{
	sem_wait(self->roomdata->forks_bunch);
	return (0);
}

int	takes_leftfork(t_philo *self)
{
	sem_wait(self->roomdata->forks_bunch);
	return (0);
}

int	thinks(t_philo *self)
{
	(void)self;
	return (0);
}
