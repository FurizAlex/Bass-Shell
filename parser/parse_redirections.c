/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:29:56 by rpadasia          #+#    #+#             */
/*   Updated: 2025/08/31 01:29:13 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

#define REDIRECT_IN     0
#define REDIRECT_OUT    1
#define REDIRECT_APPEND 2
#define REDIRECT_HEREDOC 3

static t_node_type	get_redirect_type(t_token_type	token_type)
{
	if (token_type == TOKEN_REDIRECT_IN)
		return (REDIRECT_IN);
	if (token_type == TOKEN_REDIRECT_OUT)
		return (REDIRECT_OUT);
	if (token_type == TOKEN_REDIRECT_APPEND)
		return (REDIRECT_APPEND);
	if (token_type == TOKEN_HEREDOC)
		return (REDIRECT_HEREDOC);
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

static t_redirection	*create_redirection(int type, char *filename)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->target = ft_strdup(filename);
	redir->next = NULL;
	return (redir);
}

static void	add_redirection(t_redirection **head, t_redirection *new_redir)
{
	t_redirection	*current;

	if (!*head)
	{
		*head = new_redir;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

/*Processes redirection operators and filenames, chains multiple redirections*/
t_ast_node	*parse_redirection(t_parser *parser, t_ast_node *cmd_node)
{
	t_redirection	*redir;
	int				redir_type;

	if (!cmd_node)
		return (NULL);
	while (is_redirect_token(parser->current_token))
	{
		redir_type = get_redirect_type(parser->current_token->type);
		advance_parser(parser);
		if (!parser->current_token || parser->current_token->type != TOKEN_WORD)
		{
			free_ast(cmd_node);
			return (NULL);
		}
		redir = create_redirection(redir_type, parser->current_token->value);
		if (!redir)
		{
			free_ast(cmd_node);
			return (NULL);
		}
		add_redirection(&cmd_node->redirections, redir);
		advance_parser(parser);
	}
	return (cmd_node);
}
