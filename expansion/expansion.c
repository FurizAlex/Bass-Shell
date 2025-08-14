/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:13:24 by alechin           #+#    #+#             */
/*   Updated: 2025/08/14 10:28:53 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

char	**join_commands(t_root *root)
{
	int		i;
	int		count;
	char	**cmd;

	i = 0;
	count = 0;
	if (!root->tokens)
		return (NULL);
	while (root->tokens[count] != NULL)
		count++;
	cmd = malloc((count + 1) * sizeof(char *));
	while (i < count)
	{
		if (!root->tokens[i]->value)
			cmd[i] = ft_strdup("");
		else
			cmd[i] = ft_strdup(root->tokens[i]->value);
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

char	**expand_commands(char **cmd, t_root *root)
{
	int		i;
	char	*temp;
	char	*quoted;

	if (!cmd)
		return (NULL);
	i = -1;
	while (cmd[++i])
	{
		temp = cmd[i];
		quoted = expand_string(temp, root);
		free(temp);
		if (!quoted)
			cmd[i] = ft_strdup("");
		else
			cmd[i] = quoted;
		if (!cmd[i])
			return (NULL);
	}
	i = -1;
	while (cmd[++i])
	{
		temp = cmd[i];
		cmd[i] = remove_quotes(temp);
		free(temp);
		if (!cmd[i])
			return (NULL);
	}
	cmd = remove_null(cmd, root);
	return (cmd);
}

char	*expand_string(char *str, t_root *root)
{
	int		i;
	char	*chunk;
	char	*token;
	char	*tmp;

	if (!str)
		return (NULL);
	token = ft_strdup("");
	if (!token)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		chunk = get_next_area(str, &i, root);
		if (!chunk)
		{
			free(token);
			return (NULL);
		}
		tmp = ft_strjoin(token, chunk);
		free(token);
		free(chunk);
		if (!tmp)
			return (NULL);
		token = tmp;
	}
	return (token);
}
