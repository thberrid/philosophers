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

NAME	= philo_two

C_NAME	= 	main.c 					\
			args_ctr.c 				\
			clean.c 				\
			death.c					\
			environment.c 			\
			ft_atoi.c 				\
			hypervisor.c 			\
			mutex_access.c			\
			mutex_access_apply.c	\
			mutex_access_ctr.c		\
			philo_actions.c			\
			print.c 				\
			routine.c 				\
			time.c

OBJ_NAME  = $(C_NAME:.c=.o)
OBJ_DIR	  = obj
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(OBJ_NAME))

CFLAGS	= -Wall -Wextra -Werror -g3 #-fsanitize=address

.PHONY: all
all : $(NAME)

$(NAME) : $(OBJ_FILES)
	$(CC) $(CFLAGS) -pthread -I . $(OBJ_FILES) -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(FILES_H)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I . -c -o $@ $<

.PHONY: clean
clean :
	rm -f $(OBJ_FILES)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re : fclean all
