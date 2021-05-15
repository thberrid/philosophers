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

#include <philo_three.h>

static t_todolist	*get_todolist(void)
{
	static t_todolist todolist[6] = {
		{ &thinks, &takes_leftfork, &update_time, has_taken_a_fork },
		{ &thinks, &takes_rightfork, &update_time, has_taken_a_fork },
		{ &update_mealtime, &eats, &thinks, is_eating },
		{ &update_time, &sleeps, &thinks, is_sleeping },
		{ &update_time, &thinks, &thinks, is_thinking },
		{ NULL, NULL, NULL, died }
	};

	return (todolist);
}

int				routine(t_philo *self)
{
	int				current_state;
	t_todolist		*todo;

	todo = get_todolist();
	current_state = 0;
	self->forks_bunch = sem_open(SEMNAME_FORKS, 0);
	self->printer = sem_open(SEMNAME_PRINTER, 0);
	if (self->id % 2)
		usleep(1000);
	while (1)
	{
		self->state.id = todo[current_state].state;
		todo[current_state].pre_task(self);
		if (!todo[current_state].task(self))
		{
			todo[current_state].post_task(self);
			current_state += 1;
			if (!todo[current_state].task)
				current_state = 0;
		}
		if (is_this_the_end(self))
			break ;
	}
	return (0);
}
