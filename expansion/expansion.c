/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:13:24 by alechin           #+#    #+#             */
/*   Updated: 2025/09/01 17:06:33 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

static int	expand_each_command(char **cmd, t_minishell *msh)
{
	int		i;
	char	*temp;
	char	*quoted;

	i = -1;
	while (cmd[++i])
	{
		temp = cmd[i];
		quoted = expand_string(temp, msh);
		free(temp);
		if (!quoted)
			cmd[i] = ft_strdup("");
		else
			cmd[i] = quoted;
		if (!cmd[i])
			return (-1);
	}
	return (0);
}

static int	remove_each_quote(char **cmd)
{
	int		i;
	char	*temp;

	i = -1;
	while (cmd[++i])
	{
		temp = cmd[i];
		cmd[i] = remove_quotes(temp);
		free(temp);
		if (!cmd[i])
			return (-1);
	}
	return (0);
}

char	**expand_commands(char **cmd, t_minishell *msh)
{
	if (!cmd)
		return (NULL);
	if (expand_each_command(cmd, msh) == -1)
		return (NULL);
	if (remove_each_quote(cmd) == -1)
		return (NULL);
	cmd = remove_null(cmd, msh);
	return (cmd);
}

static int	expand_loop(char *str, int *i, char **token, t_minishell *msh)
{
	char	*chunk;
	char	*tmp;

	while (str[*i] != '\0')
	{
		chunk = get_next_area(str, i, msh);
		if (!chunk)
		{
			free(*token);
			return (-1);
		}
		tmp = ft_strjoin(*token, chunk);
		free(*token);
		free(chunk);
		if (!tmp)
			return (-1);
		*token = tmp;
	}
	return (0);
}

char	*expand_string(char *str, t_minishell *msh)
{
	int		i;
	char	*token;

	if (!str || !msh)
		return (NULL);
	token = ft_strdup("");
	if (!token)
		return (NULL);
	i = 0;
	if (expand_loop(str, &i, &token, msh) == -1)
		return (NULL);
	return (token);
}
