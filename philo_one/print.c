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

int state_print(t_philo *self)
{
	t_mtxdata *printer;

	printer = &self->roomdata->printer;
	mutex_access(printer, self, ctr_getdata, apply_print);
	return (0);
}

void					state_print(t_philo *self)
{
	return (mutex_access(self->roomdata->printer, ctr_print, apply_print, self->roomdata->printer->data));
	
	char			*state_str;
	long			state_time;

	pthread_mutex_lock(&(self->roomdata->printer));
	if (self->roomdata->table.state == OPEN)
	{
		
		state_str = states_desc[self->state.id].str;
		state_time = tv_to_ms(&self->state.time) - tv_to_ms(&self->roomdata->birth);
			printf("%14ld %d %s\n", state_time, self->id, state_str);
		if (self->state.id == died)
			self->roomdata->table.state = CLOSED;
	}
	pthread_mutex_unlock(&(self->roomdata->printer));
}
