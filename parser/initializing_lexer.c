/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing_lexer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:18:38 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/13 00:51:54 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_lexer	*init_lexer(char *input)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->input = ft_strdup(input);
	lexer->pos = 0;
	lexer->current_char = lexer->input[0];
	lexer->in_single_quote = false;
	lexer->in_double_quote = false;

	return (lexer);
}

void	free_lexer(t_lexer *lexer)
{
	if (lexer)
	{
		free(lexer->input);
		free(lexer);
	}
}