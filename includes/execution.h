/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:33:54 by alechin           #+#    #+#             */
/*   Updated: 2025/08/27 16:59:00 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

/* -- Error Handling -- */
int				error2exit(char *msg, int status);
int				error4exit(char *msg, int status);
int				error6exit(char *msg, int status);

/* -- Built-ins -- */
int				koi_cd(char **cmd, t_minishell *e);
int				koi_echo(char **cmd);
int				koi_env(t_minishell *e);
int				koi_exit(char **cmd, t_minishell *msh);
int				koi_pwd(void);
int				koi_unset(char **cmd, t_minishell *msh);
int				koi_export(t_minishell *e, char **env);
int				handle_export(char **cmd, t_minishell *e);

/* -- Execution Built-ins -- */
int				specify(char **cmd, t_minishell *e);
int				is_builtin(char **cmd, t_minishell *std);

/* -- Export Helper -- */
void			no_args(t_minishell *e);
int				valid_name(char *env);
int				valid_environment(char *env, t_minishell *e);
char			**appends(char **env, t_minishell *e, char *new_variable);

/* -- AST Tree Handling -- */


/* -- Shell Loop -- */
void			shell_loop(void);


/* -- Execution Main -- */
int				execute_ast(t_ast_node *node);
int				execute_pipe_node(t_ast_node *node);
int				execute_heredoc_node(t_ast_node *node);
int				execute_redirect_append(t_ast_node *node);
int				execute_redirect_out(t_ast_node *node);
int				execute_redirect_in(t_ast_node *node);
int				execute_command_node(t_ast_node *node);
char 			*expand_var(char *prefix, char *dollar, int vlen, t_minishell *msh);
char 			*expand_literal_dollar(char *prefix, char *dollar, t_minishell *msh);
char 			*expand_question(char *prefix, t_minishell *msh, char *rest);


/* -- Execution Path -- */
char			*exec_path(char *cmd, char **env);

/* -- Execution External -- */
int				external(char **cmd, t_minishell *msh);

/* -- Pipe -- */


/* -- Redirections Exec -- */
int				redir_type(int type);

/* -- Expansion Main -- */
char			*remove_quotes(char *str);
char			**expand_commands(char **cmd, t_minishell *msh);
char			*expand_string(char *str, t_minishell *msh);

/* -- Expansion Helper -- */
char			**remainders(char **cmd, t_minishell *msh, int box, int keep);
char			*remove_quotes_size(char *str, int *i);
char			**remove_null(char **cmd, t_minishell *msh);
char			*get_raw_area(char *str, int *i);
char			*get_next_area(char *str, int *i, t_minishell *msh);

/* -- Env -- */
int				variable_len(char *start);
char			*to_get_env(char *start, int len, t_minishell *msh);

/* -- Dollar -- */
char			*join_free_both(char *a, char *b);
char			*join_free_first(char *a, char *b);
char			*expand_dollar(char *prompt, t_minishell *msh);

/* -- Termination -- */

void			terminate_tokens(t_token **tokens);

/* -- Cleanup -- */
void			cleanup_execution(t_minishell *msh);

/* -- Initialization -- */
void			initialise(int *argc, char ***argv, t_token **tokens, char **env);

/* -- Tree Binary System -- */

void			set_token_prev_pointers(t_token *head);
void			check_quotes_in_value(char *value, bool *s_q, bool *d_q);


/* -- Export Helper -- */
void			free_split(char **arr);
void			print_export(t_minishell *e);
char			**sort_env(char **env);



t_minishell		*minishell(void);

#endif