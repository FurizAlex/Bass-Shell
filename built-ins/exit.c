/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:27 by alechin           #+#    #+#             */
/*   Updated: 2025/06/18 17:28:55 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	_exit(char **cmd)
{
	int			argc;
	t_minishell	*msh;

	argc = countword(cmd);
	ft_putstr_fd("exit\n", 2);
	else if (argc > 2)
		return (error6exit("Error: Too many arguments", 2));
	if (argc == 1)
		msh->status = 0;
	else if (sdigit(cmd[1]) == 1)
	{
		error6exit("Error: A number must be put in", 2);
		msh->status = 2;
	}
	msh->status = ft_atoi(cmd[1]) & 255;
	/* Todo()! -- Add the rest l8r*/
	exit(msh->status);
}