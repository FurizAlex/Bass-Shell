/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:06:17 by rpadasia          #+#    #+#             */
/*   Updated: 2025/09/03 01:38:52 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execution.h"
#include "../includes/parsing.h"

static int	apply_all_redirections(t_redirection *redir, int *saved_fds)
{
	while (redir)
	{
		if (apply_redirection(redir, saved_fds) != 0)
		{
			restore_fds(saved_fds);
			return (1);
		}
		redir = redir->next;
	}
	return (0);
}

static int	execute_command_type(char **args, t_minishell *msh)
{
	int	builtin_result;

	builtin_result = is_builtin(args, msh);
	if (builtin_result != -1)
		return (builtin_result);
	else
		return (external(args, msh));
}

int	execute_command_and_redirects(t_ast_node *node)
{
	int				saved_fds[2];
	int				result;
	t_minishell		*msh;

	saved_fds[0] = -1;
	saved_fds[1] = -1;
	if (!node || !node->args || !node->args[0])
		return (0);
	msh = minishell();
	node->args = expand_commands(node->args, msh);
	if (apply_all_redirections(node->redirections, saved_fds) != 0)
		return (1);
	result = execute_command_type(node->args, msh);
	restore_fds(saved_fds);
	return (result);
}

int	execute_pipe(t_ast_node *node)
{
	int		pipe_fd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		right_status;

	if (!node || !node->left || !node->right)
		return (1);
	if (handle_pipe_creation(pipe_fd) != 0)
		return (1);
	if (create_and_fork_processes(pipe_fd, node, &left_pid, &right_pid) != 0)
		return (1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &right_status, 0);
	handle_signal_output(right_status);
	reset_signals_interactive();
	return (get_exit_status(right_status));
}

// Main AST execution function
int	execute_ast(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (execute_command_and_redirects(node));
	else if (node->type == NODE_PIPE)
		return (execute_pipe(node));
	else
		return (1);
}
