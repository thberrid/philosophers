/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:44:48 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/11 11:44:50 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

int	usage_write(void)
{
	write(1, P_USAGE, P_USAGE_LEN);
	return (0);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		nb;

	sign = 1;
	i = 0;
	nb = 0;
	while (*str && ft_isspace(*str))
		str += 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str += 1;
	while (*str && ft_isdigit(*str))
	{
		nb *= 10;
		nb += *(str + i) - '0';
		str += 1;
	}
	return (nb * sign);
}