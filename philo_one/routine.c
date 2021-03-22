/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 11:12:49 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/21 11:12:51 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

static void			update_time(t_philo *self)
{
	gettimeofday(&self->state.time, NULL);
	state_print(self);
}

static void			update_mealdata(t_philo *self)
{
	self->meals.count += 1;
	gettimeofday(&self->meals.time, NULL);
	gettimeofday(&self->state.time, NULL);
	state_print(self);
}

void				dies(t_philo *self)
{
	gettimeofday(&self->state.time, NULL);
	self->state.id = died;
	state_print(self);
}

static t_todolist	*get_todolist(void)
{
	static t_todolist todolist[6] = {
		{ &thinks, &takes_leftfork, &update_time, has_taken_a_fork },
		{ &thinks, &takes_rightfork, &update_time, has_taken_a_fork },
		{ &update_mealdata, &eats, &thinks, is_eating },
		{ &update_time, &sleeps, &thinks, is_sleeping },
		{ &update_time, &thinks, &thinks, is_thinking },
		{ NULL, NULL, NULL, died }
	};

	return (todolist);
}


static int	is_dead(t_philo *self)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (self->meals.count == 0)
	{
		if (tv_to_ms(&now) - tv_to_ms(&self->roomdata->birth)
			>= self->roomdata->tt_die)
			return (1);
	}
	else
	{
		if (tv_to_ms(&now) - tv_to_ms(&self->meals.time)
			>= self->roomdata->tt_die)
			return (1);
	}
	return (0);
}

int			is_this_the_end(t_philo *self)
{
	if (mutex_access(&self->roomdata->printer, self, noctr, apply_getdata))
		return (1);
	if (is_dead(self))
	{
		dies(self);
		return (1);
	}
	return (0);
}

void				*routine(void *data)
{
	int				current_state;
	t_philo			*philo;
	t_todolist		*todo;

	todo = get_todolist();
	philo = (t_philo *)data;
	current_state = 0;
//	if (philo->id % 2)
//		usleep(1000);
	while (1)
	{
		philo->state.id = todo[current_state].state;
		todo[current_state].pre_task(philo);
		if (todo[current_state].task(philo))
			continue ;
		todo[current_state].post_task(philo);
		current_state += 1;
		if (!todo[current_state].task)
			current_state = 0;
		if (is_this_the_end(philo))
			break ;
	}
	return (philo);
}
