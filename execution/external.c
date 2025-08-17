/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:14:25 by alechin           #+#    #+#             */
/*   Updated: 2025/08/14 10:17:18 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

/*
static void	run(char **cmd, t_minishell *msh)
{
	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, msh->env);
	ft_putstr_fd(cmd[0], 2);
	array2clear(cmd);
	error2exit(" ", 127);
}*/

static char	*get_env_value(char **envp, char *key)
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

static int	search(char **cmd, t_minishell *msh)
{
	int		i;
	char	**paths;
	char	*candidate;
	char	*cut;
	char	*path_env;

	path_env = get_env_value(msh->env, "PATH");
	if (!cmd || !cmd[0] || !path_env)
		return (127);
	cut = ft_strjoin("/", cmd[0]);
	if (!cut)
		return (127);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (free(cut), 127);
	i = 0;
	while (paths[i])
	{
		candidate = ft_strjoin(paths[i], cut);
		if (candidate && access(candidate, X_OK) == 0)
		{
			execve(candidate, cmd, msh->env);
			perror(candidate);
			_exit(126);
		}
		free(candidate);
		i++;
	}
	array2clear(paths);
	free(cut);
	return (127);
}

static int	child(char **cmd, t_minishell *msh)
{
	if (!cmd || !cmd[0])
		_exit(127);
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
	{
		if (access(cmd[0], X_OK) == 0)
		{
			execve(cmd[0], cmd, msh->env);
			perror(cmd[0]);
			_exit(126);
		}
		perror(cmd[0]);
		_exit(127);
	}
	_exit(search(cmd, msh));
}

int	external(char **cmd, t_minishell *msh)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		error2exit("Fishy Error: Couldn't fork pid", 1);
		return (1);
	}
	if (pid == 0)
		child(cmd, msh);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
