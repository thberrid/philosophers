/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:10:52 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/23 13:11:02 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_two.h>

static int	is_dead(t_philo *self)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (self->meals.count == 0)
	{
		if (tv_to_ms(&now) - tv_to_ms(&self->roomdata->birth)
			>= self->roomdata->tt.die)
			return (1);
	}
	else
	{
		if (tv_to_ms(&now) - tv_to_ms(&self->meals.time)
			>= self->roomdata->tt.die)
			return (1);
	}
	return (0);
}

void		dies(t_philo *self)
{
	gettimeofday(&self->state.time, NULL);
	self->state.id = died;
	state_print(self);
}

int			is_this_the_end(t_philo *self)
{
	/*
	if (mutex_access(&self->roomdata->printer, self, noctr, apply_getdata))
		return (1);
	*/
	if (is_dead(self))
	{
		dies(self);
		return (1);
	}
	return (0);
}
