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

void eats(t_philo *self)
{
	usleep(self->roomdata->tt_eat * 1000);
	pthread_mutex_unlock(&self->neighboor->fork);
	pthread_mutex_unlock(&self->fork);
}

void sleeps(t_philo *self)
{
	usleep(self->roomdata->tt_sleep * 1000);
}

void takes_leftfork(t_philo *self)
{
	pthread_mutex_lock(&(self->fork));
}

void takes_rightfork(t_philo *self)
{
	pthread_mutex_lock(&(self->neighboor->fork));
}

void	thinks(t_philo *self)
{
	(void)self;
	return ;
}

void	update_time(t_philo *self)
{
	gettimeofday(&self->state.time, NULL);
}

void	update_mealdata(t_philo *self)
{
	gettimeofday(&self->state.time, NULL);
	gettimeofday(&self->meals.time, NULL);
	self->meals.count += 1;
}

t_todolist	*get_todolist()
{
	static t_todolist todolist[6] = {
		{ &update_time, &takes_leftfork, has_taken_a_fork },
		{ &update_time, &takes_rightfork, has_taken_a_fork },
		{ &update_mealdata, &eats, is_eating },
		{ &update_time, &sleeps, is_sleeping },
		{ &update_time, &thinks, is_thinking },
		{ NULL, NULL, died }
	};
	return (todolist);
}

int		is_dead(t_philo *self)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (tv_to_ms(&now) - tv_to_ms(&self->meals.time) >= self->roomdata->tt_die)
		return (1);
	return (0);
}

int		should_i_go(t_philo *self)
{
	if (self->roomdata->table.state == CLOSED)
	{
		pthread_mutex_unlock(&self->roomdata->printer);
		return (1);
	}
	if (is_dead(self))
	{
		gettimeofday(&self->state.time, NULL);
		self->state.id = died;
		state_print(self);
		self->roomdata->table.state = CLOSED;
		pthread_mutex_unlock(&self->roomdata->printer);
		return (1);
	}
	return (0);
}

void	*routine(void *data)
{
	int				index;
	t_philo 		*philo;
	t_todolist		*todo;

	todo = get_todolist();
	philo = (t_philo *)data;
	index = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->roomdata->printer);
		if (should_i_go(philo))
			return (philo);
		todo[index].before(philo);
		philo->state.id = todo[index].state;
		todo[index].task(philo);
		state_print(philo);
		pthread_mutex_unlock(&philo->roomdata->printer);
		if (!todo[index].task)
			index = 0;
	}
	return (philo);
}