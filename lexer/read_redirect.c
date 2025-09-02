/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:59:27 by rpadasia          #+#    #+#             */
/*   Updated: 2025/09/02 22:22:26 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/*  char current = lexer->current_char;
    char next = peek_char(lexer);
	Recognizes <, >, <<, >> operators, advances lexer appropriately
*/
static t_token	*read_infile(t_lexer *lexer, char next)
{
	advance_lexer(lexer);
	if (next == '<')
	{
		advance_lexer(lexer);
		return (create_token(TOKEN_HEREDOC, "<<", false));
	}
	return (create_token(TOKEN_REDIRECT_IN, "<", false));
}

static t_token	*read_outfile(t_lexer *lexer, char next)
{
	advance_lexer(lexer);
	if (next == '>')
	{
		advance_lexer(lexer);
		return (create_token(TOKEN_REDIRECT_APPEND, ">>", false));
	}
	return (create_token(TOKEN_REDIRECT_OUT, ">", false));
}

t_token	*read_redirect(t_lexer *lexer)
{
	char	current;
	char	next;

	current = lexer->current_char;
	next = peek_char(lexer);
	if (current == '<')
		return (read_infile(lexer, next));
	if (current == '>')
		return (read_outfile(lexer, next));
	return (NULL);
}
