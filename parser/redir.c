/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 22:59:21 by rpadasia          #+#    #+#             */
/*   Updated: 2025/08/31 02:36:58 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

#define REDIRECT_IN     0
#define REDIRECT_OUT    1
#define REDIRECT_APPEND 2
#define REDIRECT_HEREDOC 3

void	restore_fds(int *saved_fds)
{
	if (saved_fds[0] != -1)
	{
		dup2(saved_fds[0], STDIN_FILENO);
		close(saved_fds[0]);
		saved_fds[0] = -1;
	}
	if (saved_fds[1] != -1)
	{
		dup2(saved_fds[1], STDOUT_FILENO);
		close(saved_fds[1]);
		saved_fds[1] = -1;
	}
}

int	apply_redirect_in(char *filename, int *saved_fds)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		return (1);
	}
	if (saved_fds[0] == -1)
		saved_fds[0] = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	apply_redirect_out(char *filename, int *saved_fds)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(filename);
		return (1);
	}
	if (saved_fds[1] == -1)
		saved_fds[1] = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redirect_append(char *filename, int *saved_fds)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(filename);
		return (1);
	}
	if (saved_fds[1] == -1)
		saved_fds[1] = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redirection(t_redirection *redir, int *saved_fds)
{
	char	*filename;
	char	*temp;
	int		result;

	if (!redir || !redir->target)
		return (1);
	filename = expand_string(redir->target, minishell());
	if (!filename)
		return (1);
	temp = filename;
	filename = remove_quotes(filename);
	free(temp);
	result = 1;
	if (redir->type == REDIRECT_IN)
		result = apply_redirect_in(filename, saved_fds);
	else if (redir->type == REDIRECT_OUT)
		result = apply_redirect_out(filename, saved_fds);
	else if (redir->type == REDIRECT_APPEND)
		result = apply_redirect_append(filename, saved_fds);
	else if (redir->type == REDIRECT_HEREDOC)
		result = apply_redirect_heredoc(filename, saved_fds);
	free(filename);
	return (result);
}
