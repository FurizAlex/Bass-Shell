/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:12:56 by alechin           #+#    #+#             */
/*   Updated: 2025/06/26 16:27:46 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int	redir_type(int type)
{
	return (type == TOKEN_REDIRECT_IN
		|| TOKEN_REDIRECT_OUT
		|| TOKEN_REDIRECT_APPEND
		|| TOKEN_HEREDOC);
}

int	redirect_prompt(t_root *root)
{
	int	status;

	status = 0;
	if (!root)
		return (1);
	if (root->left)
		status = redirect_prompt(root->left);
	if (status)
		return (status);
	if (redir_type(root->tokens[0]->type))
	{
		status = redirection(root);
		if (status)
			return (status);
	}
	if (root->right)
		status = redirect_prompt(root->right);
	if (status)
		return (status);
	if (!redir_type(root->tokens[0]->type))
		/* execute the command */
	return (0);
}

int	redirection(t_root *root)
{
	int		types;
	char	*filename;
	char	*quote_filename;
	t_redir *redir

	types = NULL;
	filename = NULL;
	if (root->tokens[0]->type != TOKEN_HEREDOC)
	{
		expand_string(filename);
		remove_quotes(filename);
		free(filename);
	}
	if (root->tokens[0]->type == TOKEN_REDIRECT_IN)
		types = in(filename);
	if (root->tokens[0]->type == TOKEN_REDIRECT_OUT)
		types = out(filename);
	if (root->tokens[0]->type == TOKEN_REDIRECT_APPEND)
		types = append(filename);
	if (root->tokens[0]->type == TOKEN_HEREDOC)
		types = heredoc(filename, redir->type);
	free(filename);
	return (types);
}
