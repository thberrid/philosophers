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

#include <philo_three.h>

int	is_goal_achieved(t_philo *self)
{
	t_roomdata *roomdata;

	roomdata = self->roomdata;
	if (roomdata->max_meals > 0 && self->meals.count >= roomdata->max_meals)
		return (1);
	return (0);
}

void	process_detroy(t_philo *philos, int len)
{
	int		index;

	index = 0;
	while (index < len)
	{
		kill(philos[index].pid, 9);
		index += 1;
	}
}

int		processes_gather(t_philo *philos, int len)
{
	int		status;

	waitpid(-1, &status, 0);
	if (status == (1 << STATUS_DEAD))
	{
		process_detroy(philos, philos->roomdata->philos_len);
		clean(philos, philos[0].roomdata);
	}
	else if (status == (1 << STATUS_EATGOAL))
	{
		if (len > 1)
			return (processes_gather(philos, len - 1));
		clean(philos, philos->roomdata);
	}
	return (0);
}

int		processes_launch(t_philo *philos, t_roomdata *roomdata)
{
	int		index;
	int		max;
	pid_t	pid;

	index = 0;
	max = roomdata->philos_len;
	gettimeofday(&roomdata->birth, NULL);
	while (index < max)
	{
		pid = fork();
		if (pid < 0)
		{
			write(1, "fork problem\n", 13);
			process_detroy(philos, index);
			clean(philos, philos[0].roomdata);
			return (1);
		}
		if (!pid)
			return (routine(&philos[index]));
		philos[index].pid = pid;
		index += 1;
	}
	processes_gather(philos, roomdata->philos_len);
	return (0);
}