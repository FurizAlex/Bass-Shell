/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:33:54 by alechin           #+#    #+#             */
/*   Updated: 2025/08/11 16:52:37 by furizalex        ###   ########.fr       */
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
int				koi_env(t_env *env);
int				koi_exit(char **cmd, t_root *root, t_token *token, t_minishell *msh);
int				koi_pwd(void);
int				koi_unset(char **cmd, t_root *root);
int				koi_export(t_minishell *e, char **env);
int				handle_export(char **cmd, t_minishell *e);

/* -- Execution Built-ins -- */
int				specify(char **cmd, t_minishell *e, t_env *env);
int				is_builtin(char **cmd, t_minishell *std);

/* -- Export Helper -- */
void			no_args(t_minishell *e);
int				valid_name(char *env);
int				valid_environment(char *env, t_minishell *e);
char			**appends(char **env, t_minishell *e, char *new_variable);

/* -- AST Tree Handling -- */
int				priority(t_token *curr);
void			current_order(t_token *curr, t_token **choice, int *priority);
void			reset(t_token **tokens, t_micro *shell);
t_token			*find_position(t_token **tokens, int id);

/* -- Shell Loop -- */
void			shell_loop(void);

/* -- Branching -- */
int				is_fork(t_root *root);
int				execute_status(t_root *root);
void			dup2io(int io_in, int io_out);

/* -- Execution Main -- */
char			type_null(t_root *root);
int				execute_prompt(t_root *root, t_minishell *msh);
int				execution(t_root *root);

/* -- Execution Path -- */
char			*exec_path(char *cmd, char **env);

/* -- Execution External -- */
int				external(char **cmd, t_minishell *msh);

/* -- Pipe -- */
void			pipex(t_root *root);

/* -- Redirections Exec -- */
int				redir_type(int type);
int				redirect_prompt(t_root *root);
int				redirection(t_root *root);

/* -- Redirections Operations -- */
int				in(char *filename);
int				out(char *filename);
int				append(char *filename);
int				heredoc(char *filename, t_root *root, t_lexer *lexer);
int				heredoc_checker(t_root **root);

/* -- Expansion Main -- */
char			*remove_quotes(char *str);
char			**join_commands(t_root *root);
char			**expand_commands(char **cmd, t_root *root);
char			*expand_string(char *str, t_root *root);

/* -- Expansion Helper -- */
char			**remainders(char **cmd, t_root *root, int box, int keep);
char			*remove_quotes_size(char *str, int *i);
char			**remove_null(char **cmd, t_root *root);
char			*get_raw_area(char *str, int *i);
char			*get_next_area(char *str, int *i, t_root *root);

/* -- Env -- */
int				variable_len(char *start);
char			*to_get_env(char *start, int len, t_root *root);

/* -- Dollar -- */
char			*expand_dollar(char *prompt, t_root *root);

/* -- Termination -- */
void			terminate_ast(t_root **root);
void			terminate_tokens(t_token **tokens);

/* -- Cleanup -- */
void			cleanup_execution(t_minishell *msh);

/* -- Initialization -- */
void			initialise(int *argc, char ***argv, t_token **tokens, char **env);

/* -- Tree Binary System -- */
bool			set(t_root **root, t_token *curr, int list);
int				insertation(t_root **root, t_root **new, bool right);
t_root			*new(t_root **root, t_token *token, t_micro shell);

int				box_length(t_token *token);
bool			out_of_bounds(t_token *root, t_micro shell, bool outbox);
t_micro			micro_editor(t_micro shell, t_token *token, bool right);
int				recursive_tree(t_root **root, t_micro shell, t_token **token, bool right);
int				ast(t_root **root, t_token **tokens);

void			level(t_token **tokens, t_micro *shell);
void			splitters(t_token **tokens, t_micro *shell, t_token **choice);
t_token			*operators(t_token **tokens, t_micro *shell, int *priority);

int				priority(t_token *curr);
int				determine_level(t_token *tokens, int *level, int *prev_s, int *prev_d);
void			current_order(t_token *curr, t_token **choice, int *priority);
void			reset(t_token **tokens, t_micro *shell);
t_token			*find_position(t_token **tokens, int id);

void			set_token_prev_pointers(t_token *head);
void			check_quotes_in_value(char *value, bool *s_q, bool *d_q);
t_root			*create_initial_root(t_token **tokens, t_micro *shell);

/* -- Export Helper -- */
void			free_split(char **arr);
void			print_export(t_minishell *e);
char			**sort_env(char **env);

t_minishell		*minishell(void);

#endif