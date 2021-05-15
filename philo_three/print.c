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

#include <philo_three.h>

t_states_desc	*get_statesdesc(void)
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

void			state_print(t_philo *self)
{
	t_states_desc	*states_desc;
	long			state_time;
	char			*state_str;

	sem_wait(self->printer);
	if (self->state.id == died)
		self->roomdata->status = CLOSED;
	if (self->state.id == is_eating)
		self->meals.count += 1;
	states_desc = get_statesdesc();
	state_str = states_desc[self->state.id].str;
	state_time = tv_to_ms(&self->state.time) - tv_to_ms(&self->roomdata->birth);
	printf("%14ld %d %s\n", state_time, self->id, state_str);
	sem_post(self->printer);
}
