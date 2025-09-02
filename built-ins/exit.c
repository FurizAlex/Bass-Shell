/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:27 by alechin           #+#    #+#             */
/*   Updated: 2025/09/02 10:22:36 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

static int	is_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	koi_exit(char **cmd, t_minishell *msh)
{
	int	argc;
	int	code;

	argc = countword(cmd);
	ft_putstr_fd("Exit\n", 2);
	if (argc > 2)
	{
		error6exit("Error: Too many arguments\n", 2);
		return (1);
	}
	if (argc == 1)
		code = 0;
	else if (!is_number(cmd[1]))
	{
		error6exit("Error: A number must be put in\n", 2);
		code = 2;
	}
	else
		code = ft_atoi(cmd[1]) & 255;
	array2clear(cmd);
	array2clear(msh->env);
	free(msh->export);
	exit(code);
}
