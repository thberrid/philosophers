/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_access_apply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:42:12 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/22 15:42:26 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

int		apply_print(t_mtxdata *obj, t_philo *self)
{
	t_states_desc	*states_desc;
	long			state_time;
	char			*state_str;

	if (self->state.id == died)
		obj->data = CLOSED;
	if (self->state.id == is_eating)
		self->meals.count += 1;
	states_desc = get_statesdesc();
	state_str = states_desc[self->state.id].str;
	state_time = tv_to_ms(&self->state.time) - tv_to_ms(&self->roomdata->birth);
	printf("%14ld %d %s\n", state_time, self->id, state_str);
	return (0);
}

int		apply_close(t_mtxdata *obj, t_philo *useless)
{
	(void)useless;
	obj->data = CLOSED;
	return (0);
}

int		apply_getdata(t_mtxdata *obj, t_philo *useless)
{
	(void)useless;
	return (obj->data);
}

int		apply_fork_free(t_mtxdata *obj, t_philo *useless)
{
	(void)useless;
	obj->data = FREE;
	return (0);
}

int		apply_fork_take(t_mtxdata *obj, t_philo *self)
{
	obj->data = self->id;
	return (0);
}
