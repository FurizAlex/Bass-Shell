/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:13:38 by alechin           #+#    #+#             */
/*   Updated: 2025/08/24 20:20:34 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "execution.h"

static int	is_empty(char *s)
{
	if (!s)
		return (1);
	if (s[0] == '\0')
		return (1);
	return (0);
}

char	**remainders(char **cmd, t_minishell *msh, int box, int keep)
{
	char	**new;
	int		i;
	int		j;

	(void)msh;
	i = 0;
	j = 0;
	new = malloc((keep + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (cmd[i])
	{
		if (!(i < box && cmd[i][0] == '\0'))
		{
			new[j] = cmd[i];
			j++;
		}
		else
			free(cmd[i]);
		i++;
	}
	new[j] = NULL;
	free(cmd);
	return (new);
}

char	**remove_null(char **cmd, t_minishell *msh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(void)msh;
	while (cmd[i])
	{
		if (!is_empty(cmd[i]))
			cmd[j++] = cmd[i];
		else
			free(cmd[i]);
		i++;
	}
	cmd[j] = NULL;
	return (cmd);
}

char	*get_raw_area(char *str, int *i)
{
	char	quote;
	int		start;
	int		end;
	char	*ret;

	if (!str || !i)
		return (NULL);
	quote = 0;
	start = *i;
	if (str[*i] == '\'' || str[*i] == '"')
	{
		quote = str[*i];
		(*i)++;
	}
	end = *i;
	if (quote)
	{
		while (str[end] && str[end] != quote)
			end++;
		if (str[end] == quote)
			end++;
	}
	else
	{
		while (str[end] && str[end] != '\'' && str[end] != '"')
			end++;
	}
	*i = end;
	ret = dupnxtra(str + start, end - start);
	return (ret);
}

char	*get_next_area(char *str, int *i, t_minishell *msh)
{
	char	*raw;
	char	*res;

	raw = get_raw_area(str, i);
	if (!raw)
		return (NULL);
	if (raw[0] == '\'')
		res = raw;
	else
	{
		res = expand_dollar(raw, msh);
		free(raw);
	}
	return (res);
}
