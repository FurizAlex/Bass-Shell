/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:41:40 by alechin           #+#    #+#             */
/*   Updated: 2025/06/27 15:51:08 by alechin          ###   ########.fr       */
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

static void	initalize_pipes(int **pipex, int n)
{
	int	i;
	int	total;

	i = 0;
	total = (n - 1) * 2;
	pipex = malloc(sizeof(int) * total);
	while (i < n - 1)
	{
		if (pipe(&total[i * 2]) == -1)
			error2exit("Fishy Error: Couldn't get pipe");
		i++;
	}
	return ;
}

int	pipe(t_root *root)
{
	int		i;
	int		*pid;
	int		*pipex;
	char	**cmd;
	char	n;

	initalize_pipes(&pipex, n);
	i = 0;
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
