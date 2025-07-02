/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:20:48 by rpadasia          #+#    #+#             */
/*   Updated: 2025/07/02 09:59:27 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/*Handles pipe operator precedence: command | command | command*/
t_ast_node	*parse_pipeline(t_parser *parser)
{
	t_ast_node	*left;
	t_ast_node	*pipe_node;

	left = parse_command(parser);
	while (parser->current_token && parser->current_token->type == TOKEN_PIPE)
	{
		advance_parser(parser);
		pipe_node = create_ast_node(NODE_PIPE);
		if (!pipe_node)
		{
			free_ast(left);
			return (NULL);
		}
		pipe_node->left = left;
		pipe_node->right = parse_command(parser);
		if (!pipe_node->right)
		{
			free_ast(pipe_node);
			return (NULL);
		}
		left = pipe_node;
	}
	return (left);
}
