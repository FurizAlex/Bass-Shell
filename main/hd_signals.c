/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:45:05 by rpadasia          #+#    #+#             */
/*   Updated: 2025/08/20 16:58:31 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/execution.h"

extern int g_signal;

void	handle_sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		write(STDOUT_FILENO, "\n", 1);
		exit(g_signal);
	}
}

void	handle_sigeof_heredoc(int sig)
{
	(void)sig;
	printf("\n");
	g_signal = EXIT_SUCCESS;
	exit(g_signal);
}

void	setup_signals_heredoc(void)
{
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
// Set signals for heredoc context;
//EOF handling is done by checking readline return value

int	heredoc_with_signals(char *delimiter)
{
	char	*line;
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) == -1)
		return (error2exit("Couldn't create pipe for heredoc", 1));
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (error2exit("Couldn't fork for heredoc", 1));
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
			if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
				&& line[ft_strlen(delimiter)] == '\0')
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

		if (WIFEXITED(status))
			g_signal = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_signal = 128 + WTERMSIG(status);
		reset_signals_interactive();
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	return (0);
}

int	heredoc_checker_enhanced(t_root **root)
{
	char	*delimiter;

	if ((*root)->tokens && (*root)->tokens[0]->type == TOKEN_HEREDOC)
	{
		if (!(*root)->tokens[1] || !(*root)->tokens[1]->value)
			return (error2exit("No delimiter for heredoc", 1));
		delimiter = (*root)->tokens[1]->value;
		if ((delimiter[0] == '"' || delimiter[0] == '\'')
			&& ft_strlen(delimiter) >= 2)
		{
			delimiter = remove_quotes(delimiter);
		}
		return (heredoc_with_signals(delimiter));
	}
	return (UNDECLARED);
}
