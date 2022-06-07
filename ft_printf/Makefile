# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/17 11:19:27 by mpeharpr          #+#    #+#              #
#    Updated: 2022/05/19 10:51:48 by mpeharpr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HEADER = ft_printf.h
SRCS = ft_printf.c ft_putnbr_base.c ft_types.c ft_utils.c
OBJS = $(SRCS:.c=.o)

$(NAME):
	gcc -Wall -Wextra -Werror -Iinc/ -c $(SRCS)
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
