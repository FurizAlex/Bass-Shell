/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:46:35 by furizalex         #+#    #+#             */
/*   Updated: 2025/08/19 14:18:25 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Literally exist for norminette reasons */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

static void	try_exec(char *candidate, char **cmd, t_minishell *msh)
{
	if (candidate && access(candidate, X_OK) == 0)
	{
		execve(candidate, cmd, msh->env);
		perror(candidate);
		_exit(126);
	}
	free(candidate);
}

char	*get_env_value(char **envp, char *key)
{
	int		len;
	int		i;

	if (!envp || !key)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	exec_in_path(char **paths, char *cut, char **cmd, t_minishell *msh)
{
	int		i;
	char	*candidate;

	i = 0;
	while (paths[i])
	{
		candidate = ft_strjoin(paths[i], cut);
		try_exec(candidate, cmd, msh);
		i++;
	}
	return (127);
}

int	counter(t_root *node)
{
	if (!node)
		return (0);
	if (!node->left && !node->right)
		return (1);
	return (counter(node->left) + counter(node->right));
}

void	close_pipe(int *pipe, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		close(pipe[i]);
		i++;
	}
}
