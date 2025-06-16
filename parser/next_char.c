/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:26:42 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/13 03:22:46 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	advance_lexer(t_lexer *lexer)
{
	lexer->pos++;
	if (lexer->pos >= (int)ft_strlen(lexer->input))
		lexer->current_char = '\0';
	else
		lexer->current_char = lexer->input[lexer->pos];
}

char	peek_char(t_lexer *lexer)
{
	int	peek_pos;

	peek_pos = lexer->pos + 1;
	if (peek_pos >= (int)ft_strlen(lexer->input))
		return ('\0');
	return (lexer->input[peek_pos]);
}