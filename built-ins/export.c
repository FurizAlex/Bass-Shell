/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:29 by alechin           #+#    #+#             */
/*   Updated: 2025/09/01 13:24:33 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

static int	valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_no_value(t_minishell *e, char *name)
{
	int	len;
	int	i;

	if (!valid_identifier(name))
		return (error2exit("export: not a valid identifier", 1), 1);
	len = ft_strlen(name);
	i = -1;
	while (e->env[++i])
		if (!ft_strncmp(e->env[i], name, len) && e->env[i][len] == '\0')
			return (0);
	e->env = appends(e->env, e, name);
	return (0);
}

static int	export_with_value(t_minishell *e, char *env)
{
	char	*name;
	int		len;
	int		i;

	name = ft_substr(env, 0, variable_len(env));
	if (!valid_identifier(name))
	{
		free(name);
		return (error2exit("export: not a valid identifier", 1), 1);
	}
	free(name);
	len = variable_len(env);
	i = -1;
	while (e->env[++i])
	{
		if (!ft_strncmp(e->env[i], env, len) && e->env[i][len] == '=')
		{
			free(e->env[i]);
			e->env[i] = ft_strdup(env);
			return (0);
		}
	}
	e->env = appends(e->env, e, env);
	return (0);
}

int	koi_export(t_minishell *e, char **env)
{
	if (!env || !*env)
	{
		print_export(e);
		return (0);
	}
	if (ft_strchr(*env, '='))
		return (export_with_value(e, *env));
	else
		return (export_no_value(e, *env));
}

int	handle_export(char **cmd, t_minishell *e)
{
	int	i;

	if (!cmd || !cmd[1])
	{
		no_args(e);
		return (0);
	}
	i = 0;
	while (cmd[++i])
	{
		if (!cmd[i] || cmd[i][0] == '\0')
			continue ;
		koi_export(e, &cmd[i]);
	}
	return (0);
}
