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
# define USAGE_STR		"usage: nb_of_philo tt_die tt_eat \
tt_sleep [nb_of_meals]\n"
# define USAGE_LEN		56

# define DEBUG			0

# define OPEN			1
# define CLOSED			0

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

typedef struct	s_table
{
	char			state;
	pthread_mutex_t	mutex;
}				t_table;

typedef struct	s_state
{
	enum e_states	id;
	struct timeval 	time;
}				t_state;

typedef struct	s_meals
{
	struct timeval 	time;
	int				count;
}				t_meals;

typedef struct	s_roomdata
{
	int				philos_len;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				max_meals;
	t_table			table;
	pthread_mutex_t	printer;
}				t_roomdata;

typedef struct	s_philo
{
	int				id;
	t_state			state;
	t_meals			meals;
	struct timeval 	birth;
	pthread_t 		thread;
	pthread_mutex_t fork;
	struct s_philo	*neighboor;
	t_roomdata		*roomdata;
}				t_philo;


typedef struct s_todolist
{
	void			(*pre_task)(t_philo *);
	void			(*task)(t_philo *);
	void			(*post_task)(t_philo *);
	enum e_states 	state;
}				t_todolist;


int				ft_atoi(const char *str);

int				data_set(int ac, char **av, t_roomdata *roomdata, t_philo **philos);
int				args_get(int ac, char **av, t_roomdata *roomdata);

int				threads_launch(t_philo *philos, t_roomdata *roomdata);
void			threads_monitor(t_philo *philo, t_roomdata *roomdata);

int				is_dead(t_philo *philo);
void			dies(t_philo *self);


long			tv_to_ms(struct timeval *tv);
void			state_print(t_philo *philo);

void			*routine(void *data);

void			threads_gather(t_philo *philos, int max);
void			clean(t_philo *philos, t_roomdata *roomdata);
void			forksmutex_destroy(t_philo *philos, int len);
void			roomdatamutex_destroy(t_roomdata *roomdata);

#endif
