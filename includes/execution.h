/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:33:54 by alechin           #+#    #+#             */
/*   Updated: 2025/07/11 18:02:26 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

/* -- Error Handling -- */
int		error2exit(char *msg, int status);
int		error4exit(char *msg, int status);
int		error6exit(char *msg, int status);

/* -- Built-ins -- */
int		koi_cd(char **cmd, t_minishell *e);
int		koi_echo(char **cmd);
int		koi_env(t_env *env);
int		koi_exit(char **cmd, t_root *root, t_token *token, t_minishell *msh);
int		koi_pwd(void);
int		koi_unset(char **cmd, t_root *root);
char	**koi_export(char *env, t_minishell *e);

/* -- Execution Built-ins -- */
int		specify(char **cmd, t_minishell *e, t_env *env);
int		is_builtin(char **cmd, t_minishell *std, char *env);

/* -- Export Helper -- */
void	no_args(t_minishell *e);
int		valid_name(char *env);
int		valid_environment(char *env, t_minishell *e);
char	**appends(char **env, t_minishell *e, int not_equals);

/* -- AST Tree Handling -- */
int		priority(t_token *curr);
void	current_order(t_token *curr, t_token **choice, int *priority);
void	reset(t_token **tokens, t_microshell *shell);
t_token	*find_position(t_token **tokens, int id);

/* -- Shell Loop -- */
void	shell_loop(void);

/* -- Branching -- */
int		is_fork(t_root *root);
int		execute_status(t_root *root);
void	dup2io(int io_in, int io_out);

/* -- Execution Main -- */
char	type_null(t_root *root);
int		execution(t_root *root);

/* -- Execution Path -- */
char	*exec_path(char *cmd, char **env);

/* -- Execution External -- */
int		external(char **cmd, t_minishell *msh);

/* -- Pipe -- */
void	pipex(t_root *root);

/* -- Redirections Exec -- */
int		redir_type(int type);
int		redirect_prompt(t_root *root);
int		redirection(t_root *root);

/* -- Redirections Operations -- */
int		in(char *filename);
int		out(char *filename);
int		append(char *filename);
int		heredoc(char *filename, t_root *root, t_lexer *lexer);

/* -- Expansion Main -- */
char	*remove_quotes(char *str);
char	**join_commands(t_root *root);
char	**expand_commands(char **cmd, t_root *root);
char	*expand_string(char *str, t_root *root);

/* -- Expansion Helper -- */
char	**remainders(char **cmd, t_root *root, int box, int keep);
char	*remove_quotes_size(char *str, int *i);
char	**remove_null(char **cmd, t_root *root);
char	*get_raw_area(char *str, int *i);
char	*get_next_area(char *str, int *i, t_root *root);

/* -- Env -- */
int		variable_len(char *start);
char	*to_get_env(char *start, int len);

/* -- Dollar -- */
char	*expand_dollar(char *prompt, t_root *root);

/* -- Termination -- */
void	terminate_ast(t_root **root);
void	terminate_tokens(t_token **tokens);

/* -- Cleanup -- */
void	cleanup_execution(t_minishell *msh);

/* -- Initialization -- */
void	initialise(int *argc, char ***argv, t_minishell *o, char ***env);

#endif