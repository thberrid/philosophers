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

void				*routine(void *data)
{
	int				current_state;
	t_philo			*philo;
	t_todolist		*todo;

	todo = get_todolist();
	philo = (t_philo *)data;
	current_state = 0;
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		philo->state.id = todo[current_state].state;
		todo[current_state].pre_task(philo);
		if (!todo[current_state].task(philo))
		{
			todo[current_state].post_task(philo);
			current_state += 1;
			if (!todo[current_state].task)
				current_state = 0;
		}
		usleep(50);
		if (is_this_the_end(philo))
			break ;
	}
	return (philo);
}
