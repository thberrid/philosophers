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

	if (get_args(ac, av, &args))
		return (usage_write());
	if (philos_alloc(&philos, &args))
		return (write(1, "init alloc error\n", 17));
	launch_routines(philos, args.p_len);
	hypervision(philos, args.p_len);
//	usleep(500 * 1000);
	clean(philos, args.p_len);
	return (0);
}