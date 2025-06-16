/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:06:26 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/13 01:14:52 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_token	*tokenize(char *input)
{
	t_lexer	*lexer;
	t_token	*tokens;
	t_token	*current;
	t_token	*token;

	lexer = init_lexer(input);
	tokens = NULL;
	current = NULL;
	while ((token = get_next_token(lexer)) && token->type != TOKEN_EOF)
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
	}
	if (current)
		current->next = token;
	else
		tokens = token;
	free_lexer(lexer);
	return (tokens);
}