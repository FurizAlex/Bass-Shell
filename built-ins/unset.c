/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:33 by alechin           #+#    #+#             */
/*   Updated: 2025/08/06 17:40:56 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	koi_unset(char **cmd, t_root *root)
{
	int		i;
	int		j;
	int		len;
	char	*temp;
	char	**env;

	if (!cmd || !*cmd)
		return (0);
	i = 0;
	len = ft_strlen(cmd[0]);
	temp = ft_strjoin(cmd[0], "=");
	if (!temp)
		return (1);
	env = root->msh->env;
	while (env[i])
	{
		if (ft_strncmp(env[i], temp, len) == 0
				&& (env[i][len] == '=' || env[i][len] == '\0'))
		{
			free(env[i]);
			j = i;
			while (env[j])
			{
				env[j] = env[j + 1];
				root->msh->export[j] = root->msh->export[j + 1];
				j++;
			}
			break ;
		}
		i++;
	}
	free(temp);
	return (0);
}
