/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:46:57 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/12 01:22:57 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->current_char != '\0'
		&& ft_isspace(lexer->current_char)
		&& !lexer->in_single_quote
		&& !lexer->in_double_quote)
	{
		advance_lexer(lexer);
	}
}