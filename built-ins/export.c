/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:29 by alechin           #+#    #+#             */
/*   Updated: 2025/07/08 17:08:18 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	equal_checker(char *env, t_minishell *e)
{
	int	i;

	i = 0;
	while (e->env[i])
	{
		if (ft_strncmp(*e->env, env, ft_strlen(env) == 0))
		{
			e->export[i] = 0;
			break ;
		}
		i++;
	}
}

char	**without_equals(t_minishell *e, char *sbl)
{
	int		i;
	char	*list;

	i = 0;
	list = ft_strjoin("=", sbl);
	if (!list)
		error2exit("Fishy Error: Couldn't join keys's in list", 1);
	if (valid_name(sbl, e))
		return (&e->env[i]);
	while (e->env[i])
	{
		if (ft_strncmp(e->env[i], sbl, ft_strlen(sbl) == 0
				&& sbl[i] == '='))
			return (e->env);
		i++;
	}
	return (appends(e->env, e, 1));
}

char	**with_equals(t_minishell *e, char *env)
{
	char	*sbl;
	int		status;
	int		i;

	i = 0;
	status = valid_environment(env, e);
	if (status == 0)
		return (e->env);
	if (status == 1)
		return (equal_checker(env, e), e->env);
	while (env[i] && env[i] == '=')
		i++;
	if (i == 0)
		return (e->env);
	sbl = dupnxtra(env, i);
	if (!sbl)
		return (NULL);
	if (valid_name(sbl, e))
	{
		free(sbl);
		return (e->env);
	}
	free(sbl);
	return (appends(&env, e, 1));
}

char	**koi_export(char *env, t_minishell *e)
{
	if (!env)
		return (NULL);
	if (ft_strchr(env, '=') == NULL)
		return (without_equals(e, env));
	return (with_equals(e, env));
}
