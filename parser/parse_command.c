/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:32:17 by rpadasia          #+#    #+#             */
/*   Updated: 2025/07/02 09:59:28 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/*Parses simple commands, collects arguments, handles redirections*/
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
