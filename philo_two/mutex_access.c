/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:12:02 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/22 15:12:15 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_two.h>

int		mutex_access
	(t_mtxdata *obj, t_philo *self,
	int (*ctr)(t_mtxdata *), int (*apply)(t_mtxdata *, t_philo *))
{
	int		retrn;

	pthread_mutex_lock(&obj->mutex);
	retrn = ctr(obj);
	if (!retrn)
		retrn = apply(obj, self);
	pthread_mutex_unlock(&obj->mutex);
	return (retrn);
}
