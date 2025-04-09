# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alechin <alechin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 10:00:50 by alechin           #+#    #+#              #
#    Updated: 2025/04/09 10:00:50 by alechin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I(HEADER_DIRECTORY)

HEADER = $(HEADER_DIRECTORY)/minishell.h

HEADER_DIRECTORY = include
OBJECT_DIRECTORY = object

SOURCE = \
