/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:27 by alechin           #+#    #+#             */
/*   Updated: 2025/08/12 10:48:33 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	koi_exit(char **cmd, t_root *root, t_token *token, t_minishell *msh)
{
	int argc;
	int code;

	argc = countword(cmd);
	ft_putstr_fd("Exit\n", 2);
	if (argc > 2)
	{
		error6exit("Error: Too many arguments", 2);
		return (1);
	}
	if (argc == 1)
		code = 0;
	else if (sdigit(cmd[1]) == 1)
	{
		error6exit("Error: A number must be put in", 2);
		code = 2;
	}
	else
		code = ft_atoi(cmd[1]) & 255;
	array2clear(cmd);
	array2clear(msh->env);
	terminate_ast(&root);
	terminate_tokens(&token);
	exit(code);
}
