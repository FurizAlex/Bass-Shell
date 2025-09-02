/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 01:29:06 by rpadasia          #+#    #+#             */
/*   Updated: 2025/09/03 01:38:46 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execution.h"
#include "../includes/parsing.h"

void	setup_left_child(int *pipe_fd, t_ast_node *node)
{
	reset_signals_for_child();
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	exit(execute_ast(node->left));
}

void	setup_right_child(int *pipe_fd, t_ast_node *node)
{
	reset_signals_for_child();
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	exit(execute_ast(node->right));
}

int	handle_fork_error(int *pipe_fd, pid_t left_pid)
{
	perror("fork");
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (left_pid > 0)
		waitpid(left_pid, NULL, 0);
	return (1);
}

int	handle_pipe_creation(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

int	create_and_fork_processes(int *pipe_fd, t_ast_node *node,
		pid_t *left_pid, pid_t *right_pid)
{
	*left_pid = fork();
	if (*left_pid < 0)
		return (handle_fork_error(pipe_fd, 0));
	if (*left_pid == 0)
		setup_left_child(pipe_fd, node);
	*right_pid = fork();
	if (*right_pid < 0)
		return (handle_fork_error(pipe_fd, *left_pid));
	if (*right_pid == 0)
		setup_right_child(pipe_fd, node);
	return (0);
}
