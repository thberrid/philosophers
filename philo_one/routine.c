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
	update_time(self);
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

void				*routine(void *data)
{
	int				index;
	t_philo			*philo;
	t_todolist		*todo;

	todo = get_todolist();
	philo = (t_philo *)data;
	index = 0;
	while (1)
	{
		if (is_this_the_end(philo))
			break ;
		philo->state.id = todo[index].state;
		todo[index].pre_task(philo);
		if (philo->roomdata->table == OPEN)
			todo[index].task(philo);
		else
			break ;
		todo[index].post_task(philo);
		index += 1;
		if (!todo[index].task)
			index = 0;
	}
	return (philo);
}
