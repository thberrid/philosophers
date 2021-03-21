/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 10:45:59 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/21 10:46:01 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

long	tv_to_ms(struct timeval *tv)
{
	return ((tv->tv_sec * 1000) + (tv->tv_usec / 1000));
}

int		ft_usleep(long tt)
{
	struct timeval	tv;
	long			start;
	long			now;

	gettimeofday(&tv, NULL);
	start = tv_to_ms(&tv);
	now = tv_to_ms(&tv);
	while (now - start < tt)
	{
		usleep(25);
		gettimeofday(&tv, NULL);
		now = tv_to_ms(&tv);
	}
	return (0);
}
