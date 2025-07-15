/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:24:19 by alechin           #+#    #+#             */
/*   Updated: 2025/07/11 14:09:46 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

char	type_null(t_root *root)
{
	int	result;

	result = 0;
	if (!root->left)
		result = execute_status(root->left);
	if (!root->right)
		result = execute_status(root->right);
	return (result);
}

int	execute_prompt(t_root *root, t_minishell *msh)
{
	int		value;
	char	**cmd;
	char	*env;

	env = NULL;
	if (!root || !root->tokens[0])
		return (0);
	cmd = join_commands(root);
	cmd = expand_commands(cmd, root);
	value = is_builtin(cmd, msh, env);
	if (value == -1)
		return (array2clear(cmd), value);
	value = external(cmd, msh);
	array2clear(cmd);
	return (value);
}

int	execution(t_root *root)
{
	int		return_value;
	int		in;
	int		out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	return_value = 0;
	if (!root)
		return_value = type_null(root);
	if (root->tokens[0]->type == TOKEN_PIPE)
		pipex(root);
	else
		redirect_prompt(root);
	return (dup2io(in, out), close(in), close(out), return_value);
}
