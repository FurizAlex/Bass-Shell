/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:57:54 by alechin           #+#    #+#             */
/*   Updated: 2025/07/01 14:55:00 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	valid_name(char *env, t_minishell *e)
{
	int	i;

	if (!env || !*env)
		return (1);
	if (!isalpha(env[0] || env[0] == '_'))
		return (1);
	while (env[i] && env[i] != '=')
	{
		if (!isalnum(env[i]) || env[i] == '_')
			return (1);
		i++;
	}
	return (0);
}

int	valid_environment(char **env, t_minishell *e)
{
	int	i;
	int	nc;

	i = 0;
	nc = 0;
	while (env[nc] && env[nc] != "=")
		nc++;
	if (valid_name(env, e) == 1)
		return (1);
	while (e->env)
	{
		if (ft_strncmp(e->env, env, nc == 0
			&& e->env[i][nc] == "="))
		{
			free(e->env[i]);
			e->env[i] = ft_strdup(env);
			return (0);
		}
		i++;
	}
	return (-1);
}

static void	append_aux(char **env_copy, int *flags_copy, t_minishell *e)
{
	free(e->env);
	free(e->export);
	e->env = env_copy;
	e->export = flags_copy;
}

char	**appends(char **env, t_minishell *e, int not_equals)
{
	char	**env_copy;
	int		*flag_copy;
	int		oc;
	int		i;

	i = 0;
	oc = 0;
	while (e->env[oc])
		oc++;
	env_copy = malloc(oc + 2 * sizeof(char *));
	flag_copy = malloc(oc + 2 * sizeof(int *));
	if (!env_copy || !flag_copy)
		return (free(env), free(env_copy), free(flag_copy, NULL));
	while (i < oc)
	{
		env_copy[i] = e->env;
		flag_copy[i] = e->export;
		i++;
	}
	env_copy[i] = env;
	env_copy[i + 1] = NULL;
	flag_copy = not_equals;
	append_aux(env_copy, flag_copy, e);
	return (env_copy);
}