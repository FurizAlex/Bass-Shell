/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:28:48 by furizalex         #+#    #+#             */
/*   Updated: 2025/08/11 15:34:20 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join_path(char *dir, char *cmd)
{
	char	*full;
	size_t	len;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full = malloc(len);
	if (!full)
		return (NULL);
	strcpy(full, dir);
	strcat(full, "/");
	strcat(full, cmd);
	return (full);
}

void	ft_execve(char **cmd, char **envp)
{
	char	*path;
	char	*full;
	char	**paths;
	int		i;

	if (!cmd || !cmd[0])
		return ;
	if (ft_strchr(cmd[0], '/'))
		execve(cmd[0], cmd, envp);
	path = getenv("PATH");
	if (!path)
		return ;
	paths = ft_split(path, ':');
	i = -1;
	while (paths && paths[++i])
	{
		full = join_path(paths[i], cmd[0]);
		execve(full, cmd, envp);
		free(full);
	}
	perror(cmd[0]);
}