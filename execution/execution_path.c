/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:41:06 by alechin           #+#    #+#             */
/*   Updated: 2025/06/24 14:05:59 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

static void	free_pipex(char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(path[i]);
	free(paths);
}

char	*exec_path(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	**pathway;
	char	*path_finder;
	
	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == NULL)
		i++;
	pathway = ft_split(env[i] + 5, ':');
	i = -1;
	while (pathway[++i])
	{
		path_finder = ft_strjoin(pathway[i], "/");
		path = ft_strjoin(path_finder, cmd);
		free(path_finder);
		if (!path)
			break ;
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	free_pipex(pathway);
	return (NULL);
}