/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:18:38 by rpadasia          #+#    #+#             */
/*   Updated: 2025/07/02 09:59:30 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/*Creates lexer state, duplicates input string,
initializes position and quote flags*/
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

/*Creates parser state pointing to token list*/
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

/*Entry point: validates → creates parser → builds AST → cleans up*/
t_ast_node	*parse(t_token *tokens)
{
	t_parser	*parser;
	t_ast_node	*ast;

	parser = init_parser(tokens);
	if (!parser)
		return (NULL);
	ast = parse_pipeline(parser);
	free_parser(parser);
	return (ast);
}
