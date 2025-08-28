/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:06:17 by rpadasia          #+#    #+#             */
/*   Updated: 2025/08/28 22:37:26 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execution.h"
#include "../includes/parsing.h"

int	execute_command_node(t_ast_node *node)
{
	t_minishell	*msh;
	int			builtin_result;

	if (!node || !node->args || !node->args[0])
		return (0);
	msh = minishell();
	node->args = expand_commands(node->args, msh);
	if (!node->args)
		return (1);
	builtin_result = is_builtin(node->args, msh);
	if (builtin_result != -1)
		return (builtin_result);
	return (external(node->args, msh));
}

int	execute_redirect_in(t_ast_node *node)
{
	int	fd;
	int	saved_stdin;
	int	result;
	char *filename;

	if (!node || !node->filename || !node->left)
		return (1);

	// FIXED: Pass minishell() instead of NULL
	filename = expand_string(node->filename, minishell());
	if (!filename)
		return (1);

	// Remove quotes from filename
	char *temp = filename;
	filename = remove_quotes(filename);
	free(temp);

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		free(filename);
		return (1);
	}

	saved_stdin = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);

	result = execute_ast(node->left);

	dup2(saved_stdin, STDIN_FILENO);
	close(fd);
	close(saved_stdin);
	free(filename);

	return (result);
}

int	execute_redirect_out(t_ast_node *node)
{
	int	fd;
	int	saved_stdout;
	int	result;
	char *filename;

	if (!node || !node->filename || !node->left)
		return (1);
	filename = expand_string(node->filename, minishell());
	if (!filename)
		return (1);
	char *temp = filename;
	filename = remove_quotes(filename);
	free(temp);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(filename);
		free(filename);
		return (1);
	}
	saved_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	result = execute_ast(node->left);
	dup2(saved_stdout, STDOUT_FILENO);
	close(fd);
	close(saved_stdout);
	free(filename);
	return (result);
}

int	execute_redirect_append(t_ast_node *node)
{
	int	fd;
	int	saved_stdout;
	int	result;
	char *filename;

	if (!node || !node->filename || !node->left)
		return (1);

	filename = expand_string(node->filename, minishell());
	if (!filename)
		return (1);

	char *temp = filename;
	filename = remove_quotes(filename);
	free(temp);

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(filename);
		free(filename);
		return (1);
	}

	saved_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);

	result = execute_ast(node->left);

	dup2(saved_stdout, STDOUT_FILENO);
	close(fd);
	close(saved_stdout);
	free(filename);

	return (result);
}

int	execute_heredoc_node(t_ast_node *node)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	int		result;
	char	*line;
	char	*delimiter;

	if (!node || !node->filename || !node->left)
		return (1);

	delimiter = remove_quotes(node->filename);
	if (!delimiter)
		return (1);

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		free(delimiter);
		return (1);
	}

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		free(delimiter);
		return (1);
	}

	if (pid == 0)
	{
		// Child process - collect heredoc input
		close(pipe_fd[0]);
		setup_signals_heredoc();

		while (1)
		{
			line = readline("o-> ");
			if (!line)
			{
				printf("Heredoc delimited by EOF\n");
				break;
			}
			if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
				&& line[ft_strlen(delimiter)] == '\0')
			{
				free(line);
				break;
			}
			write(pipe_fd[1], line, ft_strlen(line));
			write(pipe_fd[1], "\n", 1);
			free(line);
		}
		close(pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		// Parent process
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);

		int saved_stdin = dup(STDIN_FILENO);
		dup2(pipe_fd[0], STDIN_FILENO);

		result = execute_ast(node->left);

		dup2(saved_stdin, STDIN_FILENO);
		close(pipe_fd[0]);
		close(saved_stdin);

		reset_signals_interactive();
	}

	free(delimiter);
	return (result);
}

int	execute_pipe_node(t_ast_node *node)
{
	int		pipe_fd[2];
	pid_t	left_pid, right_pid;
	int		left_status, right_status;

	if (!node || !node->left || !node->right)
		return (1);

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	// Fork for left command
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
		// Left child - output goes to pipe
		reset_signals_for_child();
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exit(execute_ast(node->left));
	}

	// Fork for right command
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
		// Right child - input comes from pipe
		reset_signals_for_child();
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		exit(execute_ast(node->right));
	}

	// Parent process
	close(pipe_fd[0]);
	close(pipe_fd[1]);

	waitpid(left_pid, &left_status, 0);
	waitpid(right_pid, &right_status, 0);

	// Handle signals for display
	if (WIFSIGNALED(right_status))
	{
		int sig = WTERMSIG(right_status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 1);
	}

	reset_signals_interactive();

	// Return exit status of rightmost command
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
		return (execute_command_node(node));
	else if (node->type == NODE_REDIRECT_IN)
		return (execute_redirect_in(node));
	else if (node->type == NODE_REDIRECT_OUT)
		return (execute_redirect_out(node));
	else if (node->type == NODE_REDIRECT_APPEND)
		return (execute_redirect_append(node));
	else if (node->type == NODE_HEREDOC)
		return (execute_heredoc_node(node));
	else if (node->type == NODE_PIPE)
		return (execute_pipe_node(node));
	else
		return (1);
}