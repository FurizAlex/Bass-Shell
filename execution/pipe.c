/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:41:40 by alechin           #+#    #+#             */
/*   Updated: 2025/06/24 14:14:27 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

void	close_pipe(int *pipe, int n)
{
	int	i;

	i = 0;
	while (i < n)
		close(pipe[i++]);
}

int	child(char **argv, int *fd)
{
	return (0);
}

int	pipe(t_exec *exec)
{
	int		status;
	int		fd[2];
	int		pid[2];

	pipe(fd)
	pid[0] = fork();
	return (0);
}