/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:27 by alechin           #+#    #+#             */
/*   Updated: 2025/07/08 13:30:41 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	koi_exit(char **cmd, t_root *root, t_token *token, t_minishell *msh)
{
	int			argc;

	argc = countword(cmd);
	ft_putstr_fd("exit\n", 2);
	if (argc > 2)
		return (error6exit("Error: Too many arguments", 2));
	else if (argc == 1)
		msh->status = 0;
	else if (sdigit(cmd[1]) == 1)
	{
		error6exit("Error: A number must be put in", 2);
		msh->status = 2;
	}
	msh->status = ft_atoi(cmd[1]) & 255;
	array2clear(cmd);
	array2clear(msh->env);
	terminate_ast(&root);
	terminate_tokens(&token);
	exit(msh->status);
}
