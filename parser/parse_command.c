/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:32:17 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/19 15:24:51 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_ast_node	*parse_command(t_parser *parser)
{
	t_ast_node	*cmd_node;
	int			arg_count;

	if (!parser->current_token || parser->current_token->type != TOKEN_WORD)
		return (NULL);
	cmd_node = create_ast_node(NODE_COMMAND);
	if (!cmd_node)
		return (NULL);
	cmd_node->args = collect_command_args(parser, &arg_count);
	if (arg_count == 0)
	{
		free_ast(cmd_node);
		return (NULL);
	}
	return (parse_redirection(parser, cmd_node));
}