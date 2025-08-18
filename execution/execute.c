/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:24:19 by alechin           #+#    #+#             */
/*   Updated: 2025/08/17 23:07:27 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

char	type_null(t_root *root)
{
	int	result;

	result = 0;
	if (!root)
		return (result);
	if (root->left)
		result = execute_status(root->left);
	if (root->right)
		result = execute_status(root->right);
	return (result);
}

int	execute_prompt(t_root *root, t_minishell *msh)
{
	int		value;
	char	**cmd;

	ft_printf("DBG: execute_prompt called for cmd_head_token_id=%d\n", root->tokens[0]->id);
	if (!root || !root->tokens[0])
		return (0);
	cmd = join_commands(root);
	cmd = expand_commands(cmd, root);
	ft_printf("DBG: execute_prompt running command token_val='%s'\n", cmd && cmd[0] ? cmd[0] : "(null)");
	value = is_builtin(cmd, msh);
	if (value == -1)
	{
		if (external(cmd, msh) == -1)
			perror(cmd[0]);
		array2clear(cmd);
		return (value);
	}
	array2clear(cmd);
	return (value);
}

int	execution(t_root *root)
{
	int	in;
	int	out;
	int	ret;

	if (!root)
		return (0);
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	ret = 0;
	if (root->tokens[0]->type == TOKEN_PIPE)
		ret = pipex(root);
	else
		ret = redirect_prompt(root);
	dup2io(in, out);
	close(in);
	close(out);
	return (ret);
}