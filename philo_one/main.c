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

#include <philo_one.h>




int main(int ac, char **av)
{
	t_args			args;
	t_philo			*philos;
	pthread_t		philo;
	pthread_mutex_t frk_right;

	if (get_args(ac, av, &args))
		return (usage_write());
	if (philos_alloc(&philos, &args))
		return (write(1, "init alloc error\n", 17));
	return (0);
/*
	if (pthread_mutex_init(&frk_right, NULL))
		return (write(1, "mtx init error\n", 15));
	usleep(10000000);
	pthread_create(&philo, NULL, routine, &data);
//	gett_imeofday(&tv, NULL);
	write(1, "OK\n", 3);
	pthread_mutex_destroy(&frk_right);
//	pthread_join(philo, NULL);
	usleep(10000);
//	pthread_detach(philo);
*/
}