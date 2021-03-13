/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 23:03:35 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/11 23:03:47 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

long	get_msec(struct timeval *tv)
{
	return (tv->tv_sec * 1000 + tv->tv_usec / 1000);
}

void    ft_putnbr(long n)
{
	char	c;

	if (n < 10)
	{
		c = n + '0';
		write(1, &c, 1);
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

static t_states_desc	*get_statesdesc(void)
{
	static t_states_desc states_desc[5] = {
		{ " is thinking\n", 13 },
		{ " is eating\n", 11 },
		{ " is sleeping\n", 13 },
		{ " is dead\n", 9 },
		{ NULL, 0 }
	};
	return (states_desc);
}

void	state_print(t_philo *philo)
{
//	struct timeval	tv;
//	char			str[64];
	t_states_desc	*states_desc;
	char			*state_desc;
	unsigned long	state_time;

	states_desc = get_statesdesc();
	state_desc = states_desc[philo->state.state].desc;
	state_time = (unsigned long)(get_msec(&(philo->state.last)) - get_msec(&(philo->birth)));
	printf("%0lu %d %s\n", state_time, philo->id, state_desc);
	/*
	if (P_DEBUG)
	{
		gettimeofday(&tv, NULL);
		ft_putnbr(get_msec(&tv));
		write(1, " ", 1);
	}
	ft_putnbr(get_msec(&(philo->state.last_change)));
	write(1, " ", 1);
	ft_putnbr(philo->id);
	write(1, states->desc, states->len);
	*/
}