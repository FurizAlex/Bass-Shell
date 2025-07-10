/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:03:49 by rpadasia          #+#    #+#             */
/*   Updated: 2025/07/10 09:41:24 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/*TOKENISING FUNCTIONS*/

t_lexer		*init_lexer(char *input);
void		advance_lexer(t_lexer *lexer);
char		peek_char(t_lexer *lexer);
void		skip_whitespace(t_lexer *lexer);
t_token		*create_token(t_token_type type, char *value, bool has_expansion);
t_token		*read_word(t_lexer *lexer);
t_token		*read_redirect(t_lexer *lexer);
t_token		*get_next_token(t_lexer *lexer);
/*void		print_tokens(t_token *tokens);*/
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
// void		print_ast(t_ast_node *node, int depth);
void		free_ast(t_ast_node *node);
void		free_parser(t_parser *parser);
t_ast_node	*parse(t_token *tokens);

char		*get_history_path(void);
void		setup_history(void);
void		cleanup_history(void);
void		load_history_file(void);
void		save_history_file(void);

void		setup_signals(void);
void		handle_sigint(int sig);
void		handle_sigquit(int sig);

#endif