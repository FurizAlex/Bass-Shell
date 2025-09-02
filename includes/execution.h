/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:33:54 by alechin           #+#    #+#             */
/*   Updated: 2025/09/02 10:39:02 by furizalex        ###   ########.fr       */
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

/* -- Execution Path -- */
char			*exec_path(char *cmd, char **env);

/* -- Execution External -- */
int				external(char **cmd, t_minishell *msh);

/* -- Pipe -- */

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
bool			is_single_quoted_literal(char *s);
char			*join_free_both(char *a, char *b);
char			*join_free_first(char *a, char *b);
char			*expand_dollar(char *prompt, t_minishell *msh);

/* -- Termination -- */

void			terminate_tokens(t_token **tokens);

/* -- Cleanup -- */
void			cleanup_execution(t_minishell *msh);

/* -- Initialization -- */
void			increment_shell_level(t_minishell *e);
void			initialise(int *argc, char ***argv,
					t_token **tokens, char **env);

/* -- Tree Binary System -- */

void			set_token_prev_pointers(t_token *head);
void			check_quotes_in_value(char *value, bool *s_q, bool *d_q);

/* -- Export Helper -- */
void			free_split(char **arr);
void			print_export(t_minishell *e);
char			**sort_env(char **env);

/* -- Norminettte Helpers -- */
void			search_path_loop(char **paths, char *cut, char **cmd);
int				handle_quote(char *str, int *i, char quote);
int				handle_no_quote(char *str, int *i);
int				is_valid_identifier(char *s);

t_minishell		*minishell(void);

#endif