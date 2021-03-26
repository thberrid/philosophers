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
	t_mtxdata *printer;

	printer = &self->roomdata->printer;
	mutex_access(printer, self, ctr_is_open, apply_print);
}
