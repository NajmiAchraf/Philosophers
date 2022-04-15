# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 16:21:14 by anajmi            #+#    #+#              #
#    Updated: 2022/04/15 00:18:50 by anajmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Werror -Wextra

SOURCE = \
		./source/checking.c			\
		./source/core.c				\
		./source/ft_atoi.c			\
		./source/ft_isdigit.c		\
		./source/ft_strlen.c		\
		./source/philo.c			\
		./source/time.c

OBJS = $(SOURCE:.c=.o)

C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_BLUE = \033[1;34m
C_RES = \033[0m

.PHONY : all clean fclean re

%.o: %.c
	@gcc $(CFLAGS) -c $^ -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	@gcc $(CFLAGS) -lpthread -I/include/philo.h $(OBJS) -o $(NAME)
	@echo "$(C_GREEN)[PHILOSOPHERS MANDATORY CREATED!]$(C_RES)"

clean :
	@rm -f $(OBJS)
	@echo "$(C_RED)[PHILOSOPHERS OBJECTS DELETED!]$(C_RES)"

fclean : clean
	@rm -f $(NAME)
	@echo "$(C_RED)[PHILOSOPHERS EXECUTABLE DELETED!]$(C_RES)"

re : fclean all
