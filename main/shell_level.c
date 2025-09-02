/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:40:54 by furizalex         #+#    #+#             */
/*   Updated: 2025/09/02 22:33:55 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

static int	replace_shlvl_at(t_minishell *e, int i, long new_value)
{
	char	*newstr;
	char	buf[32];

	if (!e || !e->env || i < 0)
		return (1);
	if (new_value < 0)
		new_value = 1;
	snprintf(buf, sizeof(buf), "%ld", new_value);
	newstr = ft_strjoin("SHLVL=", buf);
	if (!newstr)
		return (1);
	free(e->env[i]);
	e->env[i] = newstr;
	return (0);
}

static int	append_shlvl_one(t_minishell *e)
{
	char	*temp;

	if (!e)
		return (1);
	temp = ft_strdup("SHLVL=1");
	if (!temp)
		return (1);
	appends(NULL, e, temp);
	free(temp);
	return (0);
}

static long	parse_shlvl_value(char *str)
{
	char	*end_pointer;
	long	value;

	if (!str)
		return (LONG_MIN);
	value = strtol(str, &end_pointer, 10);
	if (end_pointer == str || *end_pointer != '\0')
		return (LONG_MIN);
	return (value);
}

void	increment_shell_level(t_minishell *e)
{
	int		i;
	long	value;

	if (!e || !e->env)
		return ;
	i = 0;
	while (e->env[i])
	{
		if (ft_strncmp(e->env[i], "SHLVL=", 6) == 0)
		{
			value = parse_shlvl_value(e->env[i] + 6);
			if (value == LONG_MIN)
			{
				replace_shlvl_at(e, i, 1);
				return ;
			}
			if (value < 0)
				value = 0;
			replace_shlvl_at(e, i, value + 1);
			return ;
		}
		i++;
	}
	append_shlvl_one(e);
}
