/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:33 by alechin           #+#    #+#             */
/*   Updated: 2025/08/13 14:51:46 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

static void	remove_var(t_minishell *msh, char *name)
{
	int		i;
	int		len;
	char	*temp;
	char	**env;

	if (!name || !msh || !msh->env)
		return ;
	len = ft_strlen(name);
	temp = ft_strjoin(name, "=");
	if (!temp)
		return ;
	env = msh->env;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], temp, len) && (env[i][len] == '=' || env[i][len] == '\0'))
		{
			free(env[i]);
			while (env[i + 1])
			{
				env[i] = env[i + 1];
				i++;
			}
			env[i] = NULL;
			break ;
		}
		i++;
	}
	free(temp);
}

int	koi_unset(char **cmd, t_root *root)
{
	int i;

	if (!cmd)
		return (0);
	i = 0;
	while (cmd[++i])
		remove_var(root->msh, cmd[i]);
	return (0);
}
