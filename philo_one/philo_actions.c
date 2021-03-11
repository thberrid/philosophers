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

static int	philo_eats(int tt_eat, pthread_mutex_t *frk_right)
{
	write(1, "eating\n", 7);
	usleep(tt_eat);
	pthread_mutex_unlock(frk_right);
	return (0);
}

static int	philo_sleeps(int tt_sleep)
{
	write(1, "sleeping\n", 9);
	usleep(tt_sleep);
	return (0);
}

static int	philo_thinks(t_args *args, pthread_mutex_t *frk_right)
{
	int	ret;
	write(1, "thinking\n", 9);
	if ((ret = pthread_mutex_lock(frk_right)))
		return (printf("mutex lock error %d\n", ret));
	philo_eats(args->tt_eat, frk_right);
	return (0);
}

void	*routine(void *data)
{
	t_data *this_data;

	this_data = (t_data *)data;
	while (1)
	{
		if (philo_thinks(this_data->args, this_data->frk_right))
			return (data);
		philo_sleeps(this_data->args->tt_sleep);
	}
	return (data);
}