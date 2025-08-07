/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branching.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:41:25 by alechin           #+#    #+#             */
/*   Updated: 2025/08/07 15:54:19 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

static void	kill_branch_shell(t_root *root, t_minishell *msh)
{
	free(msh->export);
	terminate_ast(&root);
	terminate_tokens(root->tokens);
	array2clear(msh->env);
}

void	dup2io(int io_in, int io_out)
{
	dup2(io_in, STDIN_FILENO);
	dup2(io_out, STDOUT_FILENO);
}

int	is_fork(t_root *root)
{
	pid_t	pid;
	int		stat;

	pid = fork();
	if (root->origin == root)
	{
		fprintf(stderr, "Fatal: root origin points to itself\n");
		return -1;
	}
	if (root->origin == root)
		return (execution(root));
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		root->origin = root;
		stat = execute_status(root);
		kill_branch_shell(root, root->msh);
		exit(stat);
	}
	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		return (WIFEXITED(stat));
	return (0);
}

int	execute_status(t_root *root)
{
	int	status;

	if (!root)
		return (-1);
	status = is_fork(root);
	if (status >= 0)
		return (status);
	return (execution(root));
}
