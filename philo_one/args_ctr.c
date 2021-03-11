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

int			get_args(int ac, char **av, t_args *args)
{
	(void)ac;
	(void)av;
	if (args_len(ac))
		return (1);
	if (args_digitsonly(ac, av))
		return (1);
	args->p_len = ft_atoi(av[1]);
	args->ttdie = ft_atoi(av[2]) * 1000;
	args->tteat = ft_atoi(av[3]) * 1000;
	args->ttsleep = ft_atoi(av[4]) * 1000;
	args->meals_len = -1;
	if (ac > P_ARG_MINLEN)
		args->meals_len = ft_atoi(av[5]);
	return (0);
}
