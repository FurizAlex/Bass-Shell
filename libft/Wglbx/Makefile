# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alechin <alechin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 10:10:29 by alechin           #+#    #+#              #
#    Updated: 2025/07/10 12:32:47 by alechin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wglbx.a

SRC = \
	getxenv.c		\
	comp.c			\
	array2clear.c	\
	countword.c		\
	cpyenv.c		\
	measure.c		\
	ncomp.c			\
	sdigit.c		\
	valenvch.c		\
	xpathfree.c		\
	dupnxtra.c		\

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re