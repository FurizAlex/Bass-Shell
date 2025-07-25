/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:41:40 by alechin           #+#    #+#             */
/*   Updated: 2025/07/21 13:39:07 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

static void	close_pipe(int *pipe, int n)
{
	int	i;
	int	total;

	i = 0;
	total = (n - 1) * 2;
	while (i < total)
		close(pipe[i++]);
}

static void	initalize_pipes(int *pipex, int n)
{
	int				i;
	int				total;

	i = 0;
	total = (n - 1) * 2;
	pipex = malloc(sizeof(int) * total);
	while (i < n - 1)
	{
		if (pipe(pipex) == -1)
			error2exit("Fishy Error: Couldn't get pipe", 1);
		i++;
	}
	return ;
}

void	pipex(t_root *root)
{
	char	n;
	int		i;
	int		*pipex;
	pid_t	pid;

	i = 0;
	n = 0;
	pipex = NULL;
	initalize_pipes(pipex, n);
	while (i < n)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i > 0)
				dup2(pipex[(i - 1) * 2], 0);
			if (i < n - 1)
				dup2(pipex[(i * 2) - 1], 1);
			close_pipe(pipex, n);
			execution(root);
		}
		i++;
	}
	close_pipe(pipex, n);
	free(pipex);
}
