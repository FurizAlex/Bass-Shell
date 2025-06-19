/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:15:10 by alechin           #+#    #+#             */
/*   Updated: 2025/06/19 15:23:19 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int	in(char *filename, int *fd, char **env)
{
	int	infile;
	
	infile = open(filename, O_RDONLY);
	if (!infile || infile == -1)
		error2exit("🍥 Fishy Error: Could not get infile", 1);
	dup2(infile, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	/* execute the command */
}

int	out(char *filename, int *fd, char **env)
{
	int	outfile;

	outfile = open(filename, O_WRONLY, O_CREAT, O_TRUNC, 0777);
	if (!outfile || !outfile == -1)
		error2exit("🍥 Fishy Error: Could not get infile", 1);
	dup2(fd[0], 0);
	dup2(outfile, 1);
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	/* execute the command */
}

int	append(char *filename, int *fd, char **env)
{
	int	outfile;

	outfile = open(filename, O_WRONLY, O_CREAT, O_APPEND, 0777);
	if (!outfile || !outfile == -1)
		error2exit("🍥 Fishy Error: Couldn't append file", 1);
	dup2(fd[0], 0);
	dup2(outfile, 1);
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	/* execute the command */
}

int	heredoc(char *filename, int *fd, char **env, char *limiter)
{
	char *line;

	if (pipe(fd) == -1)
		error2exit("🍥 Fishy Error: Could not get infile", 1);
	while (1)
	{
		
	}
}