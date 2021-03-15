/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_ctr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:45:12 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/11 11:45:14 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

static int	args_len(int ac)
{
	if (ac <  P_ARG_MINLEN || ac >  P_ARG_MAXLEN)
		return (1);
	return (0); 
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	args_digitsonly(int ac, char **av)
{
	int		index;
	int		jndex;

	index = 1;
	while (index < ac)
	{
		jndex = 0;
		while (av[index][jndex])
		{
			if (!ft_isdigit(av[index][jndex]))
				return (1);
			jndex += 1;
		}
		index += 1;
	}
	return (0);
}

int			args_get(int ac, char **av, t_roomdata *roomdata)
{
	if (args_len(ac))
		return (1);
	if (args_digitsonly(ac, av))
		return (1);
	roomdata->philos_len = ft_atoi(av[1]);
	roomdata->tt_die = ft_atoi(av[2]);
	roomdata->tt_eat = ft_atoi(av[3]);
	roomdata->tt_sleep = ft_atoi(av[4]);
	roomdata->max_meals = -1;
	if (ac > P_ARG_MINLEN)
		roomdata->max_meals = ft_atoi(av[5]);
	return (0);
}
