/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:17:30 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/08 16:18:25 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# include <stdio.h>

# define P_ARG_MINLEN 	5
# define P_ARG_MAXLEN 	6
# define P_USAGE		"usage: nb_of_philo tt_die tt_eat \
tt_sleep [nb_of_meals]\n"
# define P_USAGE_LEN	56

typedef struct	s_args {
	int	p_len;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	meals_len;
}				t_args;

typedef struct	s_philo {
	int				id;
	struct timeval 	*birth;
	pthread_mutex_t *fork;
	struct s_philo	*neighboor;
}				t_philo;

int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_atoi(const char *str);

int		usage_write(void);
int		get_args(int ac, char **av, t_args *args);

int		philos_alloc(t_phi **philos, t_args *args);

void	*routine(void *data);

#endif
