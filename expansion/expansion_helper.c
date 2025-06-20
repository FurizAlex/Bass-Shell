/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:13:38 by alechin           #+#    #+#             */
/*   Updated: 2025/06/20 17:46:22 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "execution.h"

char	**remainder(char **cmd, t_root *root, int box, int keep)
{
	char	**new;
	int			i;
	int			j;

	i = 0;
	j = 0;
	new = malloc((keep + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (cmd[i])
	{
		if (!(i < box && root->tokens[i]->type == TOKEN_WORD
			&& cmd[i][0] == '\0'))
		{
			new[j] = cmd[i];
			j++;
		}
		else
			free(cmd[i]);
		i++;
	}
	new[j] = '\0';
	free(cmd);
	return (new);
}

char	*remove_quotes_size(char *str, char *i)
{
	int		start;
	int		end;
	char	quote;
	char	*size;

	quote = 0;
	if (str[*i] == '"' || str[*i] == "'")
	{
		quote = s[*i];
		(*i)++;
	}
	start = *i;
	end = *i;
	if (!quote)
	{
		while (str[end] && str[end] != '"' && str[end] != '\'')
			end++;
	}
	while (s[end] && s[end] != quote)
		end++;
	if (quote && str[end == quote])
		end++;
	str = dupnxtra(str + start, end - start);
	*i = end;
	return (size);
}

char	**remove_null(char **cmd, t_root *root)
{
	int	box;
	int	keep;
	int	i;

	box = 0;
	keep = 0;
	i = 0;
	while (root->tokens[box])
		box++;
	while (cmd[i])
	{
		if (!(i < box && root->tokens[i]->type == TOKEN_WORD
			&& cmd[i][0] == '\0'))
			keep++;
		i++;
	}
	return (remainder(cmd, root, box, keep));
}

char	*get_raw_area(char *str, int *i)
{
	char	quote;
	int		start;
	int		end;

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
		while (str[end] && str[end] != '\'' && str[end] != '"')
			end++;
	*i = end;
	return (dupnxtra(s + start, end - start));
}

char	*get_next_area(char *str, int *i)
{
	char	*raw;
	char	*res;
	
	raw = get_raw_area(s, i);
	if (raw[0] == '\'')
		result = raw;
	else
	{
		/* expand dollar */
		free(raw);
	}
	return (res);
}