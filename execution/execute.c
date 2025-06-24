/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:24:19 by alechin           #+#    #+#             */
/*   Updated: 2025/06/24 17:13:06 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

void	close_fds(void)
{
	t_base	*base;

	close(base->fd[0]);
	close(base->fd[1]);
	close(base->fd);
}

void	handle_single(t_exec *exec)
{
	/* to handle singles commands */
	return (0);
}

void	null_(t_root *root, )

int	execution(t_root *root)
{
	int		return_value;
	int		in;
	int		out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (!root || !*root)
		return_value = NULL;
	
}