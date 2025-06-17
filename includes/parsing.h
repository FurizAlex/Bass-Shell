/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <rpadasia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:03:49 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/17 13:58:36 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../libft/libft.h"

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,// <
	TOKEN_REDIRECT_OUT,// >
	TOKEN_REDIRECT_APPEND,// >>
	TOKEN_HEREDOC,// <<
	TOKEN_EOF,
	TOKEN_ERROR
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	bool			has_expansion;/*marks if token contains $ for expansion*/
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	char		*input;
	int			pos;
	char		current_char;
	bool		in_single_quote;
	bool		in_double_quote;
}	t_lexer;

typedef enum s_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_REIRECT_APPEND,
	NODE_HEREDOC
}	t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	char				**args;
	char				*filename;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_parser
{
	t_token	*tokens;
	t_token	*current_token;
}	t_parser;

/*TOKENISING FUNCTIONS*/

t_lexer		*init_lexer(char *input);
void		advance_lexer(t_lexer *lexer);
char		peek_char(t_lexer *lexer);
void		skip_whitespace(t_lexer *lexer);
t_token		*create_token(t_token_type type, char *value, bool has_expansion);
t_token		*read_word(t_lexer *lexer);
t_token		*read_redirect(t_lexer *lexer);
t_token		*get_next_token(t_lexer *lexer);
void		print_tokens(t_token *tokens);
void		free_tokens(t_token *tokens);
void		free_lexer(t_lexer *lexer);
t_token		*tokenize(char *input);

/*PARSING FUNCTIONS*/

t_parser	*init_parser(t_token *tokens);
void		advance_parser(t_parser *parser);
t_ast_node	*create_ast_node(t_node_type type);
t_ast_node	*parse_pipeline(t_parser *parser);
t_ast_node	*parse_command(t_parser *parser);
t_ast_node	*parse_redirection(t_parser *parser, t_ast_node *cmd_node);
char		**collect_command_args(t_parser *parser, int *arg_count);
void		print_ast(t_ast_node *node, int depth);
void		free_ast(t_ast_node *node);
void		free_parser(t_parser *parser);