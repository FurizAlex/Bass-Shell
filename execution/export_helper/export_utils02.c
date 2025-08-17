/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:57:54 by alechin           #+#    #+#             */
/*   Updated: 2025/08/11 13:58:53 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	valid_name(char *env)
{
	int	i;

	if (!env || !*env)
		return (1);
	if (!(ft_isalpha(env[0]) && env[0] == '_'))
		return (1);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		if (!(ft_isalnum(env[i]) || env[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}

int	valid_environment(char *env, t_minishell *e)
{
	int	i;
	int	nc;

	i = 0;
	nc = 0;
	if (!env)
		return (-1);
	while (env[nc] && env[nc] != '=')
		nc++;
	if (valid_name(env) == 1)
		return (1);
	while (e->env && e->env[i])
	{
		if (ft_strncmp(e->env[i], env, nc) == 0
				&& (e->env[i][nc] == '=' || e->env[i][nc] == '\0'))
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
	array2clear(e->env);
	free(e->export);
	e->env = env_copy;
	e->export = flags_copy;
}

char	**appends(char **env, t_minishell *e, char *new_variable)
{
	char **env_copy;
	int *flag_copy;
	int oc;
	int i;

	(void)env;
	oc = 0;
	while (e->env && e->env[oc])
		oc++;
	env_copy = malloc((oc + 2) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	flag_copy = malloc((oc + 2) * sizeof(int));
	if (!flag_copy)
	{
		free(env_copy);
		return (NULL);
	}
	i = 0;
	while (i < oc)
	{
		env_copy[i] = ft_strdup(e->env[i]);
		if (!env_copy[i])
		{
			while (--i >= 0)
				free(env_copy[i]);
			free(env_copy);
			free(flag_copy);
			return (NULL);
		}
		flag_copy[i] = e->export[i];
		i++;
	}
	env_copy[i] = ft_strdup(new_variable);
	if (!env_copy[i])
	{
		while (--i >= 0)
			free(env_copy[i]);
		free(env_copy);
		free(flag_copy);
		return (NULL);
	}
	flag_copy[i] = 1;
	i++;
	env_copy[i] = NULL;
	flag_copy[i] = 0;
	append_aux(env_copy, flag_copy, e);
	return (env_copy);
}
