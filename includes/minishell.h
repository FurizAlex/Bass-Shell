/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:16:24 by alechin           #+#    #+#             */
/*   Updated: 2025/06/24 17:35:19 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <termios.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/Wglbx/wglbx.h"

# include "execution.h"
# include "parsing.h"

# define SHELL_NAME "bass shell"
# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define PIPE_LEFT 0
# define PIPE_RIGHT 1

# define SUCCESS 0
# define FAILURE 1

typedef enum e_status
{
	NORMAL,
	QUOTE,
	DOUBLE_QUOTE,
}	t_status;

typedef struct s_root
{
	int				level;
	t_token			**tokens;
	t_minishell		*msh;
	struct s_root	*origin;
	struct s_root	*left;
	struct s_root	*right;
}	t_root;

typedef struct s_minishell
{
	int				status;
	t_env			*env_list;
	t_exec			*cmds;
	struct s_base	*base;
}	t_minishell;

typedef struct s_base
{
	char			**argv;
	int				size;
	int				type;
	int				fd[2];
	t_token			*token;
	struct s_base	*next;
	struct s_base	*prev;
}	t_base;

/* -- Error Handling -- */
int 	error2exit(char *msg, int status);
int 	error4exit(char *msg, int status);
int 	error6exit(char *msg, int status);

/* -- Branching -- */
int		is_fork(t_root *root);
int		execute_status(t_root *root);
void	dup2io(int io_in, int io_out);

/* -- Execution Main -- */
int		execution(t_root *root);

/* -- Execution Path -- */
char	*exec_path(char *cmd, char **env);

/* -- Pipe -- */

/* -- Redirections Exec -- */
int 	redir_type(int type);
int		redirection(t_redir *redir, t_token *token);

/* -- Redirections Operations -- */
int		in(char *filename);
int		out(char *filename);
int		append(char *filename);
int		heredoc(char *filename, char *limiter);

/* -- Expansion Main -- */
char	*remove_quotes(char *str);
char	**join_commands(t_root *root);
char	**expand_commands(char **cmd, t_root *root);
char	*expand_string(char *str);

/* -- Expansion Helper -- */
char	**remainder(char **cmd, t_root *root, int box, int keep);
char	*remove_quotes_size(char *str, char *i);
char	**remove_null(char **cmd, t_root *root);
char	*get_raw_area(char *str, int *i);
char	*get_next_area(char *str, int *i);

/* -- Env -- */
int		variable_len(char *start);
char	*to_get_env(char *start, int len);

/* -- Dollar -- */
char	*expand_dollar(char *prompt);

/* -- Termination -- */
void	terminate_ast(t_root **root);
void	terminate_tokens(t_token **tokens);

#endif