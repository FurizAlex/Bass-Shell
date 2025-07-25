/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:29:56 by rpadasia          #+#    #+#             */
/*   Updated: 2025/07/02 09:59:27 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/*Maps token types to AST node types for redirections*/
static t_node_type	get_redirect_type(t_token_type	token_type)
{
	if (token_type == TOKEN_REDIRECT_IN)
		return (NODE_REDIRECT_IN);
	if (token_type == TOKEN_REDIRECT_OUT)
		return (NODE_REDIRECT_OUT);
	if (token_type == TOKEN_REDIRECT_APPEND)
		return (NODE_REDIRECT_APPEND);
	if (token_type == TOKEN_HEREDOC)
		return (NODE_HEREDOC);
	return (-1);
}

/*Checks if token is any redirection operator, duh*/
static bool	is_redirect_token(t_token *token)
{
	if (!token)
		return (false);
	return (token->type == TOKEN_REDIRECT_IN
		|| token->type == TOKEN_REDIRECT_OUT
		|| token->type == TOKEN_REDIRECT_APPEND
		|| token->type == TOKEN_HEREDOC);
}

/*Processes redirection operators and filenames, chains multiple redirections*/
t_ast_node	*parse_redirection(t_parser *parser, t_ast_node *cmd_node)
{
	t_ast_node	*current;
	t_ast_node	*redirect_node;
	t_node_type	redirect_type;

	current = cmd_node;
	while (is_redirect_token(parser->current_token))
	{
		redirect_type = get_redirect_type(parser->current_token->type);
		advance_parser(parser);
		if (!parser->current_token
			|| parser->current_token->type != TOKEN_WORD)
		{
			free_ast(current);
			return (NULL);
		}
		redirect_node = create_ast_node(redirect_type);
		if (!redirect_node)
			return (free_ast(current), NULL);
		redirect_node->filename = strdup(parser->current_token->value);
		redirect_node->left = current;
		advance_parser(parser);
		current = redirect_node;
	}
	return (current);
}
