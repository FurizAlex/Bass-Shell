/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:13:55 by alechin           #+#    #+#             */
/*   Updated: 2025/08/19 13:10:27 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int	variable_len(char *start)
{
	int	i;

	if (!start || !*start)
		return (0);
	if (!(ft_isalpha((unsigned char)start[0]) || start[0] == '_'))
		return (0);
	i = 1;
	while (start[i] && (ft_isalnum((unsigned char)start[i]) || start[i] == '_'))
		i++;
	return (i);
}

char	*to_get_env(char *start, int len, t_root *root)
{
	char		*variable_name;
	char		*env_value;
	int			i;
	t_minishell	*msh;

	if (!start || len <= 0 || !root || !root->msh)
		return (NULL);
	variable_name = dupnxtra(start, len);
	if (!variable_name)
		return (NULL);
	env_value = NULL;
	msh = root->msh;
	if (msh && msh->env)
	{
		i = 0;
		while (msh->env[i])
		{
			if (ft_strncmp(msh->env[i], variable_name, len) == 0
				&& msh->env[i][len] == '=')
			{
				env_value = msh->env[i] + len + 1;
				break ;
			}
			i++;
		}
	}
	free(variable_name);
	return (env_value);
}
