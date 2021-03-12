/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hypervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:01:45 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/12 16:01:57 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>


void	hypervision(t_philo *philo, int philo_len)
{
	t_states_desc	*states_desc;
	int				goaled;
	t_philo			*first;

	first = philo;
	goaled = 0;
	states_desc = get_statesdesc();
	while (philo)
	{
		if (philo->meals.count == philo->meals.max)
			goaled += 1;
		if (philo->state.old != philo->state.current)
		{
			philo->state.old = philo->state.current;
			print_state(philo, &states_desc[philo->state.current]);
			if (philo->state.current == is_dead)
				return ;
		}
		philo = philo->neighboor;
		if (goaled == philo_len)
			return ;
		if (philo == first)
			goaled = 0;
	}
}

void	launch_routines(t_philo	*philos, int max)
{
	int		index;

	index = 0;
	while (index < max)
	{
		pthread_create(&(philos[index].thread), NULL, &routine, &philos[index]);
		index += 1;
	}
}

void	clean(t_philo *philos, int max)
{
	int		index;
	t_philo	this;

	index = 0;
	while (index < max)
	{
		this = philos[index];
		pthread_mutex_destroy(&(this.fork));
		pthread_detach(this.thread);
		index += 1;
	}
	free(philos);
}