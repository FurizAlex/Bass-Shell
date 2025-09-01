/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:16:53 by alechin           #+#    #+#             */
/*   Updated: 2025/09/01 14:56:28 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <termios.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/Wglbx/wglbx.h"

# define SHELL_NAME "bass shell"
# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SUCCESS 0
# define FAILURE -1

# define UNDECLARED -1
# define REDIRECTION 0
# define COMMAND 1
# define PIPE 2
# define MICROSHELL 3
# define MEMORY 4
# define INTERACTIVE 5
# define EOFS 6

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,// <
	TOKEN_REDIRECT_OUT,// >
	TOKEN_REDIRECT_APPEND,// >>
	TOKEN_HEREDOC,// <<
	TOKEN_EOF,
	TOKEN_ERROR,
}	t_token_type;

typedef struct s_lexer
{
	char		*input;
	int			pos;
	char		current_char;
	bool		in_single_quote;
	bool		in_double_quote;
}	t_lexer;

typedef struct s_token
{
	int				id;
	t_token_type	type;
	t_lexer			*lexer;
	char			*value;
	bool			is_open;
	bool			has_expansion;/*marks if token contains $ for expansion*/
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef enum s_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_REDIRECT_APPEND,
	NODE_HEREDOC
}	t_node_type;

typedef struct s_redirection
{
	int						fd_from;
	int						type;
	char					*target;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_ast_node
{
	t_node_type			type;
	char				**args;
	t_redirection		*redirections;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_parser
{
	t_token	*tokens;
	t_token	*current_token;
}	t_parser;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_status
{
	NORMAL,
	QUOTE,
	DOUBLE_QUOTE,
}	t_status;

typedef struct s_minishell
{
	int				status;
	int				last_status;
	int				*export;
	char			**env;
	t_token			*token;
	t_env			*env_list;
	struct s_env	*lcl_env;
}	t_minishell;

#endif