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
			args_utils.c
NAME_O	= $(NAME_S:.c=.o)

FLAGS_CC	= -Wall -Wextra -Werror

.PHONY: all
all : $(NAME)

$(NAME) : $(NAME_O)
	$(CC) -I . $(NAME_O) -o $(NAME)

%.o: %.c $(FILES_H)
	$(CC) -I . -L -pthread -c -o $@ $<

.PHONY : clean
clean :
	rm -f $(NAME_O)

.PHONY : fclean
fclean : clean
	rm -f $(NAME)

.PHONY : re
re : fclean all
