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
CFLAGS = -Wall -Wextra -Werror -no-pie -g -I$(MINISHELL_HEADER_DIRECTORY)

#-Wall -Wextra -Werror

LIBFT = $(LIBFT_DIRECTORY)/libft.a

MINISHELL_HEADER = $(MINISHELL_HEADER_DIRECTORY)/minishell.h

LIBFT_DIRECTORY = libft
MINISHELL_HEADER_DIRECTORY = includes
OBJECT_DIRECTORY = object

SOURCE = 											\
	built-ins/cd.c									\
	built-ins/echo.c								\
	built-ins/env.c									\
	built-ins/exit.c								\
	built-ins/export.c								\
	built-ins/pwd.c									\
	built-ins/unset.c								\
	execution/export_helper/export_utils01.c		\
	execution/export_helper/export_utils02.c		\
	execution/builtin.c								\
	execution/cleanup.c								\
	execution/external.c							\
	execution/path.c								\
	execution/utils.c								\
	expansion/dollar.c								\
	expansion/dollar_helper.c						\
	expansion/env.c									\
	expansion/expansion.c							\
	expansion/helper.c								\
	expansion/expand_utils.c						\
	expansion/quotes.c								\
	lexer/read_redirect.c							\
	lexer/read_word.c								\
	lexer/read_word_utils.c							\
	lexer/remove_quotes.c							\
	lexer/token_utils.c								\
	lexer/tokenize.c								\
	main/error.c									\
	main/hd_signals.c								\
	main/hd_signals_utils.c							\
	main/main.c										\
	main/reset_signals.c							\
	main/shell_level.c								\
	main/shell_loop.c								\
	main/termination.c								\
	main/initialise.c								\
	main/history.c									\
	main/signalling.c								\
	parser/apply_heredoc.c							\
	parser/ast_execution_utils.c					\
	parser/ast_execution.c							\
	parser/ast_pipe_utils.c							\
	parser/create_node.c							\
	parser/freeing.c								\
	parser/initializing.c							\
	parser/next.c									\
	parser/parse_command.c							\
	parser/parse_pipes.c							\
	parser/parse_redirections.c						\
	parser/redir_utils.c							\
	parser/redir.c									\
	parser/transition.c								\

OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(SOURCE:.c=.o))

#/*~		Terminals Colors		~*/#

DEFAULT := \033[1;39m
RESET := \033[0m
GREEN := \033[1;32m
YELLOW := \033[1;33m
CYAN := \033[1;36m

#/*~			Main				~*/#

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	@echo "\n$(YELLOW)Compiling bass shell .c files...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -lreadline -o $(NAME)
	@echo "\n$(GREEN)The bassiest shell has been completed...$(RESET)"

$(OBJECT_DIRECTORY)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)\nCompiling libft files... $(RESET)"
	@make -C $(LIBFT_DIRECTORY) all --no-print-directory > /dev/null
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