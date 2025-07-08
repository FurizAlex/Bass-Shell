/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:36:14 by alechin           #+#    #+#             */
/*   Updated: 2025/07/08 18:11:15 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	specify(char **cmd, t_minishell *e)
{
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (koi_cd(cmd, e));
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (koi_echo(cmd));
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (koi_env(e->env));
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return (koi_exit(cmd, e->base));
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (koi_pwd(cmd));
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (koi_unset(cmd));
	return (-1);
}

int	is_builtin(char **cmd, t_minishell *std)
{
	int		i;
	char	**env_cpy;

	i = 0;
	env_cpy = std->env;
	if (!cmd[0])
		return (1);
	if (ft_strncmp(cmd[0], "export", 7) == 0)
	{
		if (!cmd[1])
			no_args(std);
		else if (ft_strlen(cmd[1]) > 8000)
			return (1);
		while (cmd[++i])
			std->env = _export(cmd);
		if (std->env == env_cpy)
			return (1);
		return (0);
	}
	return (specify(cmd));
}
