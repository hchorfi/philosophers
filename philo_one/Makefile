# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/06 17:44:45 by hchorfi           #+#    #+#              #
#    Updated: 2021/06/08 18:24:03 by hchorfi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

SRCS = main.c\
		error.c\
		utils.c \
		init.c \
		print.c

FLAGS = -Werror -Wextra -Wall

ASAN =  -g #-fsanitize=address
$(NAME) :
	gcc -g $(ASAN) $(SRCS) -o $(NAME)
	
all: $(NAME)

clean:

fclean:
	rm -rf $(NAME)

re: fclean all
