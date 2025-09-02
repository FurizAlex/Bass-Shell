/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:32:17 by rpadasia          #+#    #+#             */
/*   Updated: 2025/09/02 18:27:39 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/*Parses simple commands, collects arguments, handles redirections*/
t_ast_node	*parse_command(t_parser *parser)
{
	t_ast_node	*cmd_node;
	int			arg_count;

	if (!parser->current_token)
		return (NULL);
	cmd_node = create_ast_node(NODE_COMMAND);
	if (!cmd_node)
		return (NULL);
	cmd_node = parse_redirection(parser, cmd_node);
	if (!cmd_node)
	{
		return (NULL);
	}
	cmd_node->args = collect_command_args(parser, &arg_count);
	if (arg_count == 0 && !cmd_node->redirections)
	{
		free_ast(cmd_node);
		return (NULL);
	}
	return (parse_redirection(parser, cmd_node));
}
