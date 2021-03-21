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

void					ft_putnbr(long n)
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
	static t_states_desc	states_desc[7] = {
		{ "is thinking", 13 },
		{ "is eating", 11 },
		{ "is sleeping", 13 },
		{ "has taken a fork", 18 },
		{ "died", 4 },
		{ "new turn !", 4 },
		{ NULL, 0 }
	};

	return (states_desc);
}

void					state_print(t_philo *self)
{
	t_states_desc	*states_desc;
	char			*state_str;
	long			state_time;
	struct timeval	tvnow;
	long			now;

	states_desc = get_statesdesc();
	state_str = states_desc[self->state.id].str;
	state_time = tv_to_ms(&self->state.time) - tv_to_ms(&self->roomdata->birth);
	if (DEBUG)
	{
		gettimeofday(&tvnow, NULL);
		now = tv_to_ms(&tvnow) - tv_to_ms(&self->roomdata->birth);
		printf("%6ld [%6ld] %d %s\n", state_time, now, self->id, state_str);
	}
	else
	{
		if (self->roomdata->table == OPEN)
			printf("%6ld %d %s\n", state_time, self->id, state_str);
		if (self->state.id == died)
			self->roomdata->table = CLOSED;
	}
}
