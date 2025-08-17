/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:41:40 by alechin           #+#    #+#             */
/*   Updated: 2025/08/08 12:34:38 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

static int	counter(t_root *node)
{
	if (!node)
		return (0);
	if (!node->left && !node->right)
		return (1);
	return (counter(node->left) + counter(node->right));
}

static void	close_pipe(int *pipe, int total)
{
	int	i;

	i = 0;
	while (i < total)
		close(pipe[i++]);
}

static void wait_pipe(int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		wait(NULL);
		i++;
	}
}

static void	initalize_pipes(int **pipex, int n)
{
	int				i;
	int				total;

	i = 0;
	total = (n - 1) * 2;
	*pipex = malloc(sizeof(int) * total);
	if (!*pipex)
		error2exit("Fishy Error: Couldn't allocate pipe array", 1);
	while (i < n - 1)
	{
		if (pipe(*pipex + i * 2) < 0)
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
	n = counter(root);
	if (n <= 0)
		error2exit("Fishy Error: No commands to run", 1);
	initalize_pipes(&pipex, n);
	while (i < n)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i > 0)
				dup2(pipex[(i - 1) * 2], STDIN_FILENO);
			if (i < n - 1)
				dup2(pipex[(i * 2) + 1], STDOUT_FILENO);
			close_pipe(pipex, n);
			execution(root);
			exit(root->msh->last_status);
		}
		i++;
	}
	close_pipe(pipex, n);
	free(pipex);
	wait_pipe(n);
}
