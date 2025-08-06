/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:13:24 by alechin           #+#    #+#             */
/*   Updated: 2025/08/06 17:05:17 by furizalex        ###   ########.fr       */
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

	i = -1;
	while (cmd[++i])
	{
		temp = cmd[i];
		quoted = expand_string(temp, root);
		free(temp);
		cmd[i] = quoted;
	}
	i = -1;
	while (cmd[++i])
	{
		temp = cmd[i];
		cmd[i] = remove_quotes(temp);
		free(temp);
	}
	cmd = remove_null(cmd, root);
	return (cmd);
}

char	*expand_string(char *str, t_root *root)
{
	int		i;
	char	*chunk;
	char	*token;
	char	*temp;

	token = ft_strdup("");
	i = 0;
	while (str[i] != '\0')
	{
		chunk = get_next_area(str, &i, root);
		temp = ft_strjoin(token, chunk);
		free(token);
		free(chunk);
		token = temp;
	}
	return (token);
}
