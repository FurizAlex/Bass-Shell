/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 00:22:28 by rpadasia          #+#    #+#             */
/*   Updated: 2025/09/03 01:36:01 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

static int	handle_hd_fork_error(int *pipe_fd, char *clean_delim)
{
	perror("fork");
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	free(clean_delim);
	return (1);
}

static void	heredoc_child_process(int *pipe_fd, char *clean_delim)
{
	char	*line;

	close(pipe_fd[0]);
	setup_signals_heredoc();
	while (1)
	{
		line = readline("o-> ");
		if (!line)
		{
			printf("Heredoc delimited by EOF\n");
			break ;
		}
		if (ft_strncmp(line, clean_delim, ft_strlen(clean_delim)) == 0
			&& line[ft_strlen(clean_delim)] == '\0')
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	exit(EXIT_SUCCESS);
}

static void	heredoc_parent_process(int *pipe_fd, pid_t pid, int *saved_fds)
{
	int	status;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (saved_fds[0] == -1)
		saved_fds[0] = dup(STDIN_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	reset_signals_interactive();
}

int	setup_heredoc_pipe(char *delimiter, char **clean_delim, int *pipe_fd)
{
	*clean_delim = remove_quotes(delimiter);
	if (!*clean_delim)
		return (1);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		free(*clean_delim);
		return (1);
	}
	return (0);
}

int	apply_heredoc(char *delimiter, int *saved_fds)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*clean_delim;

	if (setup_heredoc_pipe(delimiter, &clean_delim, pipe_fd))
		return (1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (handle_hd_fork_error(pipe_fd, clean_delim));
	if (pid == 0)
		heredoc_child_process(pipe_fd, clean_delim);
	else
		heredoc_parent_process(pipe_fd, pid, saved_fds);
	free(clean_delim);
	return (0);
}
