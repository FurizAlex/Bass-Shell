/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:15:10 by alechin           #+#    #+#             */
/*   Updated: 2025/07/09 17:52:06 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int	in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (!fd || fd < 0)
		error2exit("🍥 Fishy Error: Could not get infile", 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	out(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY, O_CREAT, O_TRUNC, 0777);
	if (!fd || fd < 0)
		error2exit("🍥 Fishy Error: Could not get outfile", 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY, O_CREAT, O_APPEND, 0777);
	if (!fd || !(fd == -1))
		error2exit("🍥 Fishy Error: Couldn't append file", 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	heredoc(char *filename, t_root *root, t_lexer *lexer)
{
	int		pipex[2];
	char	*str;
	bool	is_expansion;

	if (pipe(pipex) <= -1)
		error2exit("🍥 Fishy Error: Could not get infile", 1);
	is_expansion = false;
	if (lexer->in_double_quote || lexer->in_single_quote)
		is_expansion = true;
	str = ft_strdup(lexer->input);
	if (is_expansion != false)
		str = expand_dollar(filename, root);
	ft_putstr_fd("", pipex[1]);
	dup2(pipex[0], STDOUT_FILENO);
	close(pipex[0]);
	close(pipex[1]);
	return (0);
}
