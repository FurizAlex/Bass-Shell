/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:13:24 by alechin           #+#    #+#             */
/*   Updated: 2025/08/19 16:59:08 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

static int	count_tokens(t_root *root)
{
	int	count;

	count = 0;
	if (!root->tokens)
		return (0);
	while (root->tokens[count] != NULL)
		count++;
	return (count);
}

char	**join_commands(t_root *root)
{
	int		i;
	int		count;
	char	**cmd;

	count = count_tokens(root);
	if (count == 0)
		return (NULL);
	cmd = malloc((count + 1) * sizeof(char *));
	i = 0;
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

static void	expand_and_quote_removal(char **cmd, t_root *root)
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
		if (quoted)
			cmd[i] = quoted;
		else
			cmd[i] = ft_strdup("");
	}
	i = -1;
	while (cmd[++i])
	{
		temp = cmd[i];
		cmd[i] = remove_quotes(temp);
		free(temp);
	}
}

char	**expand_commands(char **cmd, t_root *root)
{
	if (!cmd)
		return (NULL);
	expand_and_quote_removal(cmd, root);
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
			return (free(token), NULL);
		tmp = ft_strjoin(token, chunk);
		if (free(token), free(chunk), !tmp)
			return (NULL);
		token = tmp;
	}
	return (token);
}
