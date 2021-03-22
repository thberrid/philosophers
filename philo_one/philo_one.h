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
# define OPEN			1
# define CLOSED			0
# define FREE			1
# define TAKEN			0

typedef struct	s_states_desc
{
	char	*str;
	int		len;
}				t_states_desc;

enum			e_states
{
	is_thinking,
	is_eating,
	is_sleeping,
	has_taken_a_fork,
	died,
	debug
};

typedef struct	s_state
{
	enum e_states	id;
	struct timeval	time;
}				t_state;

typedef struct	s_meals
{
	struct timeval	time;
	int				count;
}				t_meals;

typedef struct	s_mtxdata
{
	pthread_mutex_t		mutex;
	char				data;
}				t_mtxdata;

typedef struct	s_timeto
{
	int				die;
	int				eat;
	int				sleep;
}				t_timeto;

typedef struct	s_roomdata
{
	int				philos_len;
	t_timeto		tt;
	int				goaled;
	int				max_meals;
	struct timeval	birth;
	t_mtxdata		printer;
}				t_roomdata;

typedef struct	s_philo
{
	int				id;
	pthread_t		thread;
	t_state			state;
	t_meals			meals;
	t_mtxdata		fork;
	t_roomdata		*roomdata;
	struct s_philo	*neighboor;
}				t_philo;

typedef struct	s_todolist
{
	void			(*pre_task)(t_philo *);
	void			(*task)(t_philo *);
	void			(*post_task)(t_philo *);
	enum e_states	state;
}				t_todolist;

int				ft_atoi(const char *str);
int				data_set
				(int ac, char **av, t_roomdata *roomdata, t_philo **philos);
int				args_get(int ac, char **av, t_roomdata *roomdata);
int				threads_launch(t_philo *philos, t_roomdata *roomdata);
void			threads_monitor(t_philo *philo, t_roomdata *roomdata);
void			*routine(void *data);
int				is_this_the_end(t_philo *self);
int				dies(t_philo *self);
int				eats(t_philo *self);
int				sleeps(t_philo *self);
int				takes_rightfork(t_philo *self);
int				takes_leftfork(t_philo *self);
int				thinks(t_philo *self);
long			tv_to_ms(struct timeval *tv);
int				ft_usleep(long tt);
void			state_print(t_philo *philo);
void			threads_gather(t_philo *philos, int max);
void			clean(t_philo *philos, t_roomdata *roomdata);
void			forksmutex_destroy(t_philo *philos, int len);

#endif
