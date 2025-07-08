/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:33 by alechin           #+#    #+#             */
/*   Updated: 2025/07/08 17:20:27 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	koi_unset(char **cmd, t_root *root)
{
	int		i;
	int		len;
	char	*temp;
	char	**env;

	i = 0;
	len = ft_strlen(*cmd);
	temp = ft_strjoin(cmd[0], "=");
	env = root->msh->env;
	while (env[i] && ft_strncmp(*env, temp, len - 1) != 0)
		i++;
	while (env[i++])
	{
		free(env[i]);
		if (env[i + 1] == NULL)
			env[i] = NULL;
		else if (env[i + 1] != NULL)
		{
			env[i] = ft_strdup(env[i + 1]);
			root->msh->export[i] = root->msh->export[i + 1];
		}
	}
	free(temp);
	return (0);
}
