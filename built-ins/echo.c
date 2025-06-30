/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:22 by alechin           #+#    #+#             */
/*   Updated: 2025/06/30 17:18:43 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execution.h"

static int	dash_n(char **cmd)
{
	int	i;

	i = 1;
	if (ft_strncmp(cmd[1], "-n", 3) == 0)
	{
		while (cmd[++i] != NULL)
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
		}
		return (0);
	}
	return (1);
}

int	koi_echo(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd[1])
		return (ft_printf("\n"), 0);
	if (dash_n(cmd) != 0)
	{
		while (cmd[++i])
		{
			ft_printf("%s", cmd[i]);
			if (cmd[i + 1] != NULL)
				ft_printf(" ");
		}
	}
	return (ft_printf("\n"), 0);
}

/*
int main(int argc, char **argv)
{
	if (argc == 2)
	{
		_echo(argv);
	}
}*/