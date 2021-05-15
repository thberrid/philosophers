/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:17:30 by thberrid          #+#    #+#             */
/*   Updated: 2021/03/08 16:18:25 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define P_ARG_MINLEN 	5
# define P_ARG_MAXLEN 	6
# define OPEN			0
# define CLOSED			1
# define FREE			0
# define TAKEN			1

# define EXIT_EATGOAL	1
# define STATUS_EATGOAL	8
# define EXIT_DEAD		2
# define STATUS_DEAD	9

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

typedef struct	s_timeto
{
	int				die;
	int				eat;
	int				sleep;
}				t_timeto;

# define SEMNAME_PRINTER	"PRINT"
# define SEMNAME_FORKS		"FORKS"

typedef struct	s_roomdata
{
	int				philos_len;
	t_timeto		tt;
	int				goaled;
	int				max_meals;
	char			status;
	struct timeval	birth;
	sem_t			*forks_bunch;
	sem_t			*printer;
}				t_roomdata;

typedef struct	s_philo
{
	int				id;
	pid_t			pid;
	pthread_t		thread;
	t_state			state;
	t_meals			meals;
	t_roomdata		*roomdata;
	sem_t			*forks_bunch;
	sem_t			*printer;
	struct s_philo	*neighboor;
}				t_philo;

typedef struct	s_todolist
{
	int				(*pre_task)(t_philo *);
	int				(*task)(t_philo *);
	int				(*post_task)(t_philo *);
	enum e_states	state;
}				t_todolist;

int				ft_atoi(const char *str);
int				data_set
				(int ac, char **av, t_roomdata *roomdata, t_philo **philos);
int				args_get(int ac, char **av, t_roomdata *roomdata);
int				processes_launch(t_philo *philos, t_roomdata *roomdata);
int				routine(t_philo *self);
int				is_this_the_end(t_philo *self);
int				is_room_closed(t_philo *self);
int				is_goal_achieved(t_philo *self);
void			close_room(t_roomdata *roomdata);
void			dies(t_philo *self);
int				eats(t_philo *self);
int				sleeps(t_philo *self);
int				thinks(t_philo *self);
int				update_time(t_philo *self);
int				update_mealtime(t_philo *self);
int				takes_rightfork(t_philo *self);
int				takes_leftfork(t_philo *self);
long			tv_to_ms(struct timeval *tv);
int				ft_usleep(long tt);
t_states_desc	*get_statesdesc(void);
void			state_print(t_philo *philo);
int				processes_gather(t_philo *philos, int len);
void			clean(t_philo *philos, t_roomdata *roomdata);
void			forksmutex_destroy(t_philo *philos, int len);

#endif
