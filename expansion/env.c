/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:13:55 by alechin           #+#    #+#             */
/*   Updated: 2025/09/01 13:27:53 by furizalex        ###   ########.fr       */
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

static char	*find_env_value(char **env, char *var_name, int len)
{
	int	i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*to_get_env(char *start, int len, t_minishell *msh)
{
	char	*variable_name;
	char	*env_value;

	if (!start || !msh)
		return (NULL);
	variable_name = dupnxtra(start, len);
	if (!variable_name)
		return (NULL);
	env_value = find_env_value(msh->env, variable_name, len);
	if (!env_value)
		env_value = "";
	free(variable_name);
	return (env_value);
}
