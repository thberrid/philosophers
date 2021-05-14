/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:17:18 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/08 16:20:15 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_two.h>

int		main(int ac, char **av)
{
	t_roomdata		roomdata;
	t_philo			*philos;

	if (data_set(ac, av, &roomdata, &philos))
		return (1);
	if (threads_launch(philos, &roomdata))
		return (1);
	threads_monitor(philos, &roomdata);
	threads_gather(philos, roomdata.philos_len);
	clean(philos, &roomdata);
	return (0);
}
