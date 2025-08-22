/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:03:49 by rpadasia          #+#    #+#             */
/*   Updated: 2025/08/20 16:58:31 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

extern int g_signal;
/*TOKENISING FUNCTIONS*/

t_lexer		*init_lexer(char *input);
void		advance_lexer(t_lexer *lexer);
char		peek_char(t_lexer *lexer);
void		skip_whitespace(t_lexer *lexer);
t_token		*create_token(t_token_type type, char *value, bool has_expansion);
t_token		*read_word(t_lexer *lexer);
t_token		*read_redirect(t_lexer *lexer);
t_token		*get_next_token(t_lexer *lexer);
void		free_tokens(t_token *tokens);
void		free_lexer(t_lexer *lexer);
t_token		*tokenize(char *input);
char		*process_word_content(char *raw);

/*PARSING FUNCTIONS*/

t_parser	*init_parser(t_token *tokens);
void		advance_parser(t_parser *parser);
t_ast_node	*create_ast_node(t_node_type type);
t_ast_node	*parse_pipeline(t_parser *parser);
t_ast_node	*parse_command(t_parser *parser);
t_ast_node	*parse_redirection(t_parser *parser, t_ast_node *cmd_node);
char		**collect_command_args(t_parser *parser, int *arg_count);
void		free_ast(t_ast_node *node);
void		free_parser(t_parser *parser);
t_ast_node	*parse(t_token *tokens);

/* HISTORY*/
char		*get_history_path(void);
void		setup_history(void);
void		cleanup_history(void);
void		load_history_file(void);
void		save_history_file(void);

/*SIGNALLING*/
void		handle_sigint(int sig);
void		handle_sigeof(int sig);
void		handle_sigint_heredoc(int sig);
void		handle_sigeof_heredoc(int sig);
void		setup_signals(void);
void		setup_signals_heredoc(void);
void		reset_signals_for_child(void);
void		reset_signals_interactive(void);
void		process_signal_state(t_minishell *msh);
bool		handle_eof_input(char *cmd);
void		reset_shell_state(void);
int			heredoc_with_signals(char *delimiter);
int			heredoc_checker_enhanced(t_root **root);


t_token		*ft_tokenlst(t_token *token);
t_token		*ft_newtoken(char *cmd, t_token_type type, int id);
t_lexer		*lexers(void);

#endif