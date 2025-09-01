/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:36:14 by alechin           #+#    #+#             */
/*   Updated: 2025/09/01 17:03:03 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

static int	check_simple_builtins(char **cmd, t_minishell *e)
{
	if (ft_strncmp(cmd[0], "cd", 2) == 0 && cmd[0][2] == '\0')
		return (koi_cd(cmd, e));
	if (ft_strncmp(cmd[0], "echo", 4) == 0 && cmd[0][4] == '\0')
		return (koi_echo(cmd));
	if (ft_strncmp(cmd[0], "env", 3) == 0 && cmd[0][3] == '\0')
		return (koi_env(e));
	if (ft_strncmp(cmd[0], "exit", 4) == 0 && cmd[0][4] == '\0')
		return (koi_exit(cmd, e));
	if (ft_strncmp(cmd[0], "pwd", 3) == 0 && cmd[0][3] == '\0')
		return (koi_pwd());
	if (ft_strncmp(cmd[0], "unset", 5) == 0 && cmd[0][5] == '\0')
		return (koi_unset(cmd, e));
	return (-1);
}

int	specify(char **cmd, t_minishell *e)
{
	if (!cmd || !cmd[0])
		return (-1);
	return (check_simple_builtins(cmd, e));
}

static int	handle_export_cmd(char **cmd, t_minishell *std)
{
	int		i;
	char	*dup;

	if (!cmd[1])
	{
		no_args(std);
		return (0);
	}
	i = 0;
	while (cmd[++i])
	{
		dup = ft_strdup(cmd[i]);
		if (!dup)
		{
			error2exit("Fishy Error: Strdup failed", 1);
			return (1);
		}
		handle_export(cmd, std);
		free(dup);
	}
	return (0);
}

int	is_builtin(char **cmd, t_minishell *std)
{
	if (!cmd || !cmd[0])
		return (-1);
	if (ft_strncmp(cmd[0], "export", 6) == 0 && cmd[0][6] == '\0')
		return (handle_export_cmd(cmd, std));
	return (specify(cmd, std));
}
