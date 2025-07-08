/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:06:26 by rpadasia          #+#    #+#             */
/*   Updated: 2025/07/08 11:24:35 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"


void	add_eof_token(t_token **tokens, t_token *current, t_token *eof_token)
{
	if (current)
		current->next = eof_token;
	else
		*tokens = eof_token;
}

/*link first token (if (!tokens))
link_next_token(otherwise)*/
t_token	*build_token_list(t_lexer *lexer)
{
	t_token	*tokens;
	t_token	*current;
	t_token	*token;

	tokens = NULL;
	current = NULL;
	token = get_next_token(lexer);
	while (token && token->type != TOKEN_EOF)
	{
		if (!tokens)
		{
			tokens = token;
			current = token;
		}
		else
		{
			current->next = token;
			current = token;
		}
		token = get_next_token(lexer);
	}
	add_eof_token(&tokens, current, token);
	return (tokens);
}

/*Orchestrates full tokenization:
creates lexer → builds token list → adds EOF → cleans up*/
t_token	*tokenize(char *input)
{
	t_lexer	*lexer;
	t_token	*tokens;

	lexer = init_lexer(input);
	if (!lexer)
		return (NULL);
	tokens = build_token_list(lexer);
	free_lexer(lexer);
	return (tokens);
}
