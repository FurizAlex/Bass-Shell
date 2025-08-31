/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_add_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 00:22:28 by rpadasia          #+#    #+#             */
/*   Updated: 2025/08/31 01:34:34 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

#define REDIRECT_IN     0
#define REDIRECT_OUT    1
#define REDIRECT_APPEND 2
#define REDIRECT_HEREDOC 3

int	apply_redirect_heredoc(char *filename, int *saved_fd)
{
	if (apply_heredoc(filename, saved_fd) != 0)
	{
		free(filename);
		return (1);
	}
	return (0);
}

int	apply_heredoc(char *delimiter, int *saved_fds)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	char	*line;
	char	*clean_delimiter;

	clean_delimiter = remove_quotes(delimiter);
	if (!clean_delimiter)
		return (1);

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		free(clean_delimiter);
		return (1);
	}

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		free(clean_delimiter);
		return (1);
	}

	if (pid == 0)
	{
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
			if (ft_strncmp(line, clean_delimiter, ft_strlen(clean_delimiter)) == 0
				&& line[ft_strlen(clean_delimiter)] == '\0')
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
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		if (saved_fds[0] == -1)
			saved_fds[0] = dup(STDIN_FILENO);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);

		reset_signals_interactive();
	}

	free(clean_delimiter);
	return (0);
}
