/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:26:42 by rpadasia          #+#    #+#             */
/*   Updated: 2025/07/02 09:59:29 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/*Moves to next character, handles end-of-string detection*/
void	advance_lexer(t_lexer *lexer)
{
	lexer->pos++;
	if (lexer->pos >= (int)ft_strlen(lexer->input))
		lexer->current_char = '\0';
	else
		lexer->current_char = lexer->input[lexer->pos];
}

/*Looks ahead one character without advancing position*/
char	peek_char(t_lexer *lexer)
{
	int	peek_pos;

	peek_pos = lexer->pos + 1;
	if (peek_pos >= (int)ft_strlen(lexer->input))
		return ('\0');
	return (lexer->input[peek_pos]);
}

/*Moves to next token in list*/
void	advance_parser(t_parser *parser)
{
	if (parser->current_token && parser->current_token->next)
		parser->current_token = parser->current_token->next;
}
