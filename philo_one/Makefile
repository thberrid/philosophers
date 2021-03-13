# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/08 16:22:40 by thberrid          #+#    #+#              #
#    Updated: 2021/03/08 16:22:41 by thberrid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HELL	= /bin/sh

NAME	= philo_one

NAME_S	= 	main.c \
			args_ctr.c \
			args_utils.c \
			hypervisor.c \
			philo_init.c \
			philo_actions.c \
			print.c
NAME_O	= $(NAME_S:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -g3 # -fsanitize=address

.PHONY: all
all : $(NAME)

$(NAME) : $(NAME_O)
	$(CC) $(CFLAGS) -pthread -I . $(NAME_O) -o $(NAME)

%.o: %.c $(FILES_H)
	$(CC) $(CFLAGS) -I . -c -o $@ $<

.PHONY: clean
clean :
	rm -f $(NAME_O)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re : fclean all
