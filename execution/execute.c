/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:24:19 by alechin           #+#    #+#             */
/*   Updated: 2025/06/27 11:59:42 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

void	close_fds(void)
{
	t_base	*base;

	close(base->fd[0]);
	close(base->fd[1]);
	close(base->fd);
}

void	handle_single(t_exec *exec)
{
	/* to handle singles commands */
	return (0);
}

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

	if (!root || !root->tokens[0])
		return (0);
	cmd = join_commands(root);
	cmd = expand_commands(cmd, root);
	value = is_builtin(cmd, msh);
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
	if (!root || !*root)
		return_value = NULL;
	if (root->tokens[0]->type == TOKEN_PIPE)
		/* execute pipe */
	else
		redirect_prompt(root);
	return (dup2io(in, out), close(in), close(out), return_value);
}
