/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:15:10 by alechin           #+#    #+#             */
/*   Updated: 2025/08/17 20:37:37 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int	in(char *filename)
{
    int fd;

    if (!filename)
        return (error2exit("🍥 Fishy Error: No infile provided", 1), 1);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (error2exit("🍥 Fishy Error: Could not get infile", 1), 1);
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        close(fd);
        return (error2exit("🍥 Fishy Error: dup2 failed for infile", 1), 1);
    }
    close(fd);
    return (0);
}

int	out(char *filename)
{
	int	fd;

	if (!filename)
		return (error2exit("🍥 Fishy Error: No outfile provided", 1), 1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (error2exit("🍥 Fishy Error: Could not get outfile", 1), 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (error2exit("🍥 Fishy Error: dup2 failed for outfile", 1), 1);
	}
	close(fd);
	return (0);
}

int	append(char *filename)
{
	int	fd;

	if (!filename)
		return (error2exit("🍥 Fishy Error: No append file provided", 1), 1);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (error2exit("🍥 Fishy Error: Couldn't append file", 1), 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (error2exit("🍥 Fishy Error: dup2 failed for append", 1), 1);
	}
	close(fd);
	return (0);
}

int	heredoc(char *delimiter, t_root *root)
{
	int	pipex_fd[2];
	pid_t	pid;
	int		status;

	(void)root;
	if (!delimiter)
		return (error2exit("🍥 Fishy Error: No delimiter provided for heredoc", 1), 1);
	if (pipe(pipex_fd) == -1)
		return (error2exit("🍥 Fishy Error: Could not create pipe for heredoc", 1), 1);
	pid = fork();
	if (pid == -1)
	{
		close(pipex_fd[0]);
		close(pipex_fd[1]);
		return (error2exit("🍥 Fishy Error: Fork failed for heredoc", 1), 1);
	}
	if (pid == 0)
	{
		close(pipex_fd[0]);
		read_heredoc(NULL, pipex_fd, delimiter);
		close(pipex_fd[1]);
		_exit(0);
	}
	close(pipex_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(pipex_fd[0]);
		return (1);
	}
	if (dup2(pipex_fd[0], STDIN_FILENO) < 0)
	{
		close(pipex_fd[0]);
		return (error2exit("🍥 Fishy Error: dup2 failed for heredoc", 1), 1);
	}
	close(pipex_fd[0]);
	return (0);
}
