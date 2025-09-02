/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:33 by alechin           #+#    #+#             */
/*   Updated: 2025/09/02 10:42:16 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

static void	shift_env(char **env, int start)
{
	while (env[start + 1])
	{
		env[start] = env[start + 1];
		start++;
	}
	env[start] = NULL;
}

static void	free_and_shift(char **env, int idx)
{
	free(env[idx]);
	shift_env(env, idx);
}

static void	remove_var(t_minishell *msh, char *name)
{
	int		i;
	int		len;

	if (!name || !msh || !msh->env)
		return ;
	len = ft_strlen(name);
	i = 0;
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], name, len)
			&& (msh->env[i][len] == '=' || msh->env[i][len] == '\0'))
		{
			free_and_shift(msh->env, i);
			break ;
		}
		i++;
	}
}

int	koi_unset(char **cmd, t_minishell *msh)
{
	int	i;

	if (!cmd || !cmd[1])
		return (0);
	i = 1;
	while (cmd[i])
	{
		if (!is_valid_identifier(cmd[i]))
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		else
			remove_var(msh, cmd[i]);
		i++;
	}
	return (0);
}
