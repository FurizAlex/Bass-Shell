/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:13:24 by alechin           #+#    #+#             */
/*   Updated: 2025/08/31 00:10:48 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

char	**expand_commands(char **cmd, t_minishell *msh)
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
		quoted = expand_string(temp, msh);
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
	cmd = remove_null(cmd, msh);
	return (cmd);
}

/*I CAN USE THIS FOR OTHER THINGS LIKE FILENAME*/
char	*expand_string(char *str, t_minishell *msh)
{
	int		i;
	char	*chunk;
	char	*token;
	char	*tmp;

	if (!str || !msh)
		return (NULL);
	token = ft_strdup("");
	if (!token)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		chunk = get_next_area(str, &i, msh);
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
