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
# include <stdlib.h>
# include <string.h>

# include <stdio.h>

# define P_ARG_MINLEN 	5
# define P_ARG_MAXLEN 	6
# define P_USAGE		"usage: nb_of_philo tt_die tt_eat \
tt_sleep [nb_of_meals]\n"
# define P_USAGE_LEN	56

# define P_DEBUG		0

enum			e_states
{
	is_eating,
	is_sleeping,
	is_thinking,
	is_dead
};

typedef struct	s_states_desc
{
	char	*desc;
	int		len;
}				t_states_desc;

typedef struct	s_args
{
	int	p_len;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	max_meals;
}				t_args;

typedef struct	s_action
{
	enum e_states	current;
	enum e_states	old;
	struct timeval 	last_change;
}				t_action;

typedef struct	s_philo
{
	t_action		state;
	int				id;
	struct timeval 	birth;
	pthread_t 		thread;
	pthread_mutex_t fork;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	nb_meals;
	int	max_meals;
	struct s_philo	*neighboor;
}				t_philo;

int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_atoi(const char *str);

int		usage_write(void);
int		get_args(int ac, char **av, t_args *args);

int		philos_alloc(t_philo **philos, t_args *args);

void    		ft_putnbr(long n);
long			get_msec(struct timeval *tv);
t_states_desc	*get_statesdesc(void);
void			print_state(t_philo *philo, t_states_desc *states);

void	*routine(void *data);

void	hypervision(t_philo *philo, int philo_len);
void	clean(t_philo *philos, int max);
void	launch_routines(t_philo	*philos, int max);

#endif
