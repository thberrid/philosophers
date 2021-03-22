/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_access_ctr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:41:52 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/22 15:42:04 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

int		ctr_getdata(t_mtxdata *obj)
{
	return (obj->data);
}

int		noctr(t_mtxdata *useless)
{
	(void)useless;
	return (0);
}
