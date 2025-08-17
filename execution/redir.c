/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:12:56 by alechin           #+#    #+#             */
/*   Updated: 2025/08/10 14:04:16 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int	redir_type(int type)
{
	return (type == TOKEN_REDIRECT_IN
		|| type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_REDIRECT_APPEND
		|| type == TOKEN_HEREDOC);
}

int	redirect_prompt(t_root *root)
{
	int	status;

	status = 0;
	if (!root || !root->tokens || !root->tokens[0])
		return (type_null(root));
	if (root->left)
		status = redirect_prompt(root->left);
	if (redir_type(root->tokens[0]->type))
		status = redirection(root);
	if (root->right)
		status = redirect_prompt(root->right);
	if (!redir_type(root->tokens[0]->type))
		status = execute_prompt(root, root->msh);
	return (status);
}

int	redirection(t_root *root)
{
	int		types;
	char	*filename;

	types = 0;
	filename = NULL;
	if (!root || !root->tokens || !root->tokens[0])
		return (error2exit("Fishy Error: redirection root invalid", 1), 1);
	if (root->tokens[1] && root->tokens[1]->value)
	{
		filename = expand_string(root->tokens[1]->value, root);
		if (!filename)
			return (error2exit("Fishy Error: couldn't expand filename", 1), 1);
		filename = remove_quotes(filename);
	}
	if (root->tokens[0]->type == TOKEN_REDIRECT_IN)
		types = in(filename);
	if (root->tokens[0]->type == TOKEN_REDIRECT_OUT)
		types = out(filename);
	if (root->tokens[0]->type == TOKEN_REDIRECT_APPEND)
		types = append(filename);
	if (root->tokens[0]->type == TOKEN_HEREDOC)
		types = heredoc(filename, root, root->lexer);
	free(filename);
	return (types);
}
