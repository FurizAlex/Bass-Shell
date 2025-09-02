/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:45:05 by rpadasia          #+#    #+#             */
/*   Updated: 2025/09/02 22:39:24 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/execution.h"

static void	heredoc_child_loop(int pipe_fd, char *delimiter)
{
	char	*line;

	close(pipe_fd);
	setup_signals_heredoc();
	while (1)
	{
		line = readline("o-> ");
		if (!line)
		{
			printf("Heredoc delimited by EOF\n");
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\0')
		{
			free(line);
			break ;
		}
		write(pipe_fd, line, ft_strlen(line));
		write(pipe_fd, "\n", 1);
		free(line);
	}
}

static void	heredoc_child_process(int *pipe_fd, char *delimiter)
{
	close(pipe_fd[0]);
	heredoc_child_loop(pipe_fd[1], delimiter);
	close(pipe_fd[1]);
	exit(EXIT_SUCCESS);
}

static void	handle_child_status(int status)
{
	if (WIFEXITED(status))
		g_signal = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_signal = 128 + WTERMSIG(status);
}

static void	heredoc_parent_process(int *pipe_fd, pid_t pid)
{
	int	status;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	handle_child_status(status);
	reset_signals_interactive();
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
}

int	heredoc_with_signals(char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (error2exit("Couldn't create pipe for heredoc", 1));
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (error2exit("Couldn't fork for heredoc", 1));
	if (pid == 0)
		heredoc_child_process(pipe_fd, delimiter);
	else
		heredoc_parent_process(pipe_fd, pid);
	return (0);
}
