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

#/*~			Standard			~*/#

RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I(MINISHELL_HEADER_DIRECTORY)

MINISHELL_HEADER = $(MINISHELL_HEADER_DIRECTORY)/minishell.h

SOURCE_DIRECTORY = #$todo()!
LIBFT_DIRECTORY = libft
MINISHELL_HEADER_DIRECTORY = includes
OBJECT_DIRECTORY = object

SOURCE = \

#/*~		Terminals Colors		~*/#

DEFAULT := \033[1;39m
RESET := \033[0m
GREEN := \033[1;32m
YELLOW := \033[1;33m
CYAN := \033[1;36m

#/*~			Main				~*/#

all: $(NAME)

$(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.c:
	@mkdir -p $(dir $@)
	@echo "\n$(YELLOW)Compiling bass shell .c files...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)\nCompiling libft files... $(RESET)"
	@make -C $(LIBFT_PATH) all --no-print-directory > /dev/null
	@echo "$(GREEN)\nSuccessfully compiled libft...$(RESET)"

clean:
	@$(RM) $(OBJECT_DIRECTORY)
	@echo "$(CYAN)\nSuccessfully cleaned all .o files...$(RESET)"

fclean: clean
	@clear
	@$(RM) $(NAME)
	@echo "$(CYAN)\nSuccessfully cleaned all makefiles files...$(RESET)"

clear:
	@clear

re: clear fclean all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

.PHONY: all clean fclean re valgrind