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

void	table_close_local(t_philo *philo)
{
	pthread_mutex_lock(philo->state.table_mutex);
	philo->state.table[0] = CLOSED;
	pthread_mutex_unlock(philo->state.table_mutex);
}

int	state_set(t_philo *self, enum e_states state)
{
	int		retrn;

	retrn = 0;
	pthread_mutex_lock(self->state.table_mutex);
	if (self->state.table[0] == OPEN)
	{	
		self->state.state = state;
		state_print(self);
	}
	else
		retrn = 1;
	if (state == is_dead)
		table_close_local(self);
	pthread_mutex_unlock(self->state.table_mutex);
	return (retrn);
}

int	philo_dies(t_philo *self)
{
	gettimeofday(&self->state.last, NULL);
	state_set(self, is_dead);
	return (1);
}

static int	philo_eats(t_philo *self)
{
	gettimeofday(&self->state.last, NULL);
	if (state_set(self, is_eating))
		return (1);
	self->meals.count += 1;
	gettimeofday(&self->meals.last, NULL);
	usleep(self->tt_eat);
	pthread_mutex_unlock(&(self->neighboor->fork));
	pthread_mutex_unlock(&(self->fork));
	return (0);
}

static int	philo_sleeps(t_philo *self)
{
	gettimeofday(&self->state.last, NULL);
	if (state_set(self, is_sleeping))
		return (1);
	usleep(self->tt_sleep);
	return (0);
}

static int	philo_thinks(t_philo *self)
{
	gettimeofday(&self->state.last, NULL);
	if (state_set(self, is_thinking))
		return (1);
	pthread_mutex_lock(&(self->neighboor->fork));
	if (state_set(self, took_fork))
		return (1);
	pthread_mutex_lock(&(self->fork));
	if (state_set(self, took_fork))
		return (1);
	return (0);
}

t_state_list	*get_statelist()
{
	static t_state_list statelist[4] = {
		{ &philo_thinks },
		{ &philo_eats },
		{ &philo_sleeps },
		{ NULL }
	};
	return (statelist);
}

void	*routine(void *data)
{
	int				index;
	int				retrn;
	t_philo 		*philo;
	t_state_list	*states;

	states = get_statelist();
	philo = (t_philo *)data;
	index = 0;
	retrn = 0;
	while (!retrn)
	{
		retrn = states[index].f(philo);
		index += 1;
		if (!states[index].f)
			index = 0;
	}
	return (philo);
}