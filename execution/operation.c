/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:15:10 by alechin           #+#    #+#             */
/*   Updated: 2025/08/10 14:18:00 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int	in(char *filename)
{
	int	fd;

	if (!filename)
		return (error2exit("🍥 Fishy Error: No infile provided", 1), 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error2exit("🍥 Fishy Error: Could not get infile", 1), 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
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

int	heredoc(char *filename, t_root *root, t_lexer *lexer)
{
	int		pipex[2];
	char	*str;

	(void)filename;
	str = ft_strdup(lexer->input);
	if (pipe(pipex) <= -1)
		error2exit("🍥 Fishy Error: Could not get infile", 1);
	str = root->tokens[0]->value;
	if (str)
		ft_putstr_fd(str, pipex[1]);
	close(pipex[1]);
	dup2(pipex[0], STDOUT_FILENO);
	close(pipex[0]);
	return (0);
}
