/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branching.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:41:25 by alechin           #+#    #+#             */
/*   Updated: 2025/08/24 20:05:33 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "../includes/parsing.h"

// static void	kill_branch_shell(t_root *root, t_minishell *msh)
// {
// 	free(msh->export);
// 	terminate_ast(&root);
// 	terminate_tokens(root->tokens);
// 	array2clear(msh->env);
// }

// void	dup2io(int io_in, int io_out)
// {
// 	dup2(io_in, STDIN_FILENO);
// 	dup2(io_out, STDOUT_FILENO);
// }

// int	is_fork(t_root *root)
// {
// 	pid_t	pid;
// 	int		stat;
// 	int		sig;

// 	if (!root)
// 		return (-1);
// 	signal(SIGINT, SIG_IGN);
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		reset_signals_interactive();
// 		return (-1);
// 	}
// 	if (pid == 0)
// 	{
// 		reset_signals_for_child();
// 		root->origin = root;
// 		stat = execute_status(root);
// 		kill_branch_shell(root, root->msh);
// 		exit(stat);
// 	}
// 	waitpid(pid, &stat, 0);
// 	if (WIFEXITED(stat))
// 	{
// 		root->msh->last_status = WEXITSTATUS(stat);
// 	}
// 	else if (WIFSIGNALED(stat))
// 	{
// 		sig = WTERMSIG(stat);
// 		root->msh->last_status = 128 + sig;

// 		if (sig == SIGINT)
// 			write(1, "\n", 1);
// 		else if (sig == SIGQUIT)
// 			ft_putendl_fd("Quit (core dumped)", 1);
// 	}
// 	reset_signals_interactive();
// 	return (root->msh->last_status);
// }

// int	execute_status(t_root *root)
// {
// 	int	status;

// 	if (!root)
// 		return (-1);
// 	status = is_fork(root);
// 	if (status >= 0)
// 		return (status);
// 	return (execution(root));
// }
