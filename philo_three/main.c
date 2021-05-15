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

#include <philo_three.h>

int		main(int ac, char **av)
{
	t_roomdata		roomdata;
	t_philo			*philos;

	if (data_set(ac, av, &roomdata, &philos))
		return (1);
	if (processes_launch(philos, &roomdata))
		return (1);
	return (0);
}
