/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:14:25 by alechin           #+#    #+#             */
/*   Updated: 2025/08/19 13:45:36 by furizalex        ###   ########.fr       */
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

static char	*make_cut(char *cmd0)
{
	if (!cmd0)
		return (NULL);
	return (ft_strjoin("/", cmd0));
}

static int	search(char **cmd, t_minishell *msh)
{
	char	*path_env;
	char	**paths;
	char	*cut;
	int		ret;

	path_env = get_env_value(msh->env, "PATH");
	if (!cmd || !cmd[0] || !path_env)
		return (127);
	cut = make_cut(cmd[0]);
	paths = ft_split(path_env, ':');
	if (!paths || !cut)
	{
		free(cut);
		return (127);
	}
	ret = exec_in_path(paths, cut, cmd, msh);
	array2clear(paths);
	free(cut);
	return (ret);
}

static void	exec_absolute(char **cmd, t_minishell *msh)
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

static int	child(char **cmd, t_minishell *msh)
{
	if (!cmd || !cmd[0])
		_exit(127);
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
		exec_absolute(cmd, msh);
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
