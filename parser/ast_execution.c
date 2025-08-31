/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:06:17 by rpadasia          #+#    #+#             */
/*   Updated: 2025/08/31 00:42:40 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execution.h"
#include "../includes/parsing.h"

int	execute_command_and_redirects(t_ast_node *node)
{
	t_redirection	*redir;
	int				saved_fds[2];
	int				result;
	t_minishell		*msh;
	int				builtin_result;

	saved_fds[0] = -1;
	saved_fds[1] = -1;
	if (!node || !node->args || !node->args[0])
		return (0);
	msh = minishell();
	node->args = expand_commands(node->args, msh);
	redir = node->redirections;
	while (redir)
	{
		if (apply_redirection(redir, saved_fds) != 0)
		{
			restore_fds(saved_fds);
			return (1);
		}
		redir = redir->next;
	}
	builtin_result = is_builtin(node->args, msh);
	if (builtin_result != -1)
		result = builtin_result;
	else
		result = external(node->args, msh);
	restore_fds(saved_fds);
	return (result);
}

int	execute_pipe(t_ast_node *node)
{
	int		pipe_fd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		left_status;
	int		right_status;

	if (!node || !node->left || !node->right)
		return (1);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	left_pid = fork();
	if (left_pid < 0)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (1);
	}
	if (left_pid == 0)
	{
		reset_signals_for_child();
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exit(execute_ast(node->left));
	}
	right_pid = fork();
	if (right_pid < 0)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(left_pid, NULL, 0);
		return (1);
	}
	if (right_pid == 0)
	{
		reset_signals_for_child();
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		exit(execute_ast(node->right));
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(left_pid, &left_status, 0);
	waitpid(right_pid, &right_status, 0);
	if (WIFSIGNALED(right_status))
	{
		int sig = WTERMSIG(right_status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 1);
	}
	reset_signals_interactive();
	if (WIFEXITED(right_status))
		return (WEXITSTATUS(right_status));
	else if (WIFSIGNALED(right_status))
		return (128 + WTERMSIG(right_status));
	return (1);
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