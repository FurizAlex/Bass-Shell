/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:59:27 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/29 21:46:25 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/*  char current = lexer->current_char;
    char next = peek_char(lexer);
	Recognizes <, >, <<, >> operators, advances lexer appropriately
*/

t_token	*read_redirect(t_lexer *lexer)
{
	char	current;
	char	next;

	current = lexer->current_char;
	next = peek_char(lexer);
	if (current == '<')
	{
		advance_lexer(lexer);
		if (next == '<')
		{
			advance_lexer(lexer);
			return (create_token(TOKEN_HEREDOC, "<<", false));
		}
		return (create_token(TOKEN_REDIRECT_IN, "<", false));
	}
	if (current == '>')
	{
		advance_lexer(lexer);
		if (next == '>')
		{
			advance_lexer(lexer);
			return (create_token(TOKEN_REDIRECT_APPEND, ">>", false));
		}
		return (create_token(TOKEN_REDIRECT_OUT, ">", false));
	}
	return (NULL);
}
