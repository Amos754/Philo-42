# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 12:10:39 by olmarech          #+#    #+#              #
#    Updated: 2024/09/04 02:21:45 by marechaloli      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= main.c utils.c life_habit.c initialisation.c

OBJS	= $(SRCS:.c=.o)

RM		= rm -f

NAME	= philo

CFLAGS	= -I. -Wall -Wextra -Werror

.c.o:
			@$(CC) $(CFLAGS) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJS)
				@gcc ${CFLAGS} -o ${NAME} ${OBJS}
				@echo "philo compilation : \033[;32msucces\033[0m"

clean:
			@$(RM) $(OBJS)
			@echo "files \033[1;31mdeleted\033[0m"

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean re fclean