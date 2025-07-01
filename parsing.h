/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:03:49 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/13 01:25:51 by rpadasia         ###   ########.fr       */
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