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
#include <stdio.h>

/*
int	p_sleep(void)
{
	usleep();
}

int	philo(void)
{
	while (1)
	{
		p_eat();
		p_sleep();
		p_think();
	}
	return (0);
}
*/

int main(int ac, char **av)
{
	struct timeval 	tv;
	t_args			args;

	if (get_args(ac, av, &args))
		return (usage_write());
	printf("%d\n", args.meals_len);
	gettimeofday(&tv, NULL);
	printf("%lu\n", tv.tv_sec);
	printf("lol\n");
	return (0);
}