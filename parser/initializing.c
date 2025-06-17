/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <rpadasia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:18:38 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/17 14:03:08 by rpadasia         ###   ########.fr       */
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

t_parser	*init_parser(t_token *tokens)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);

	parser->tokens = tokens;
	parser->current_token = tokens;
	return (parser);
}

