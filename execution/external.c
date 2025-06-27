/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:14:25 by alechin           #+#    #+#             */
/*   Updated: 2025/06/27 15:49:11 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

static void	run(char **cmd, t_minishell *msh)
{
	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, msh->env);
	ft_putstr_fd(cmd[0], 2);
	array2clear(cmd);
	error2exit(" ", 127);
}

static int	search(char **cmd, t_minishell *msh)
{
	int		i;
	int		count;
	char	**paths;
	char	**pathcmd;
	char	**cut_point;

	cut_point = ft_strjoin("/", cmd[0]);
	if (!getxenv("PATH", msh))
		return (free(cmd), error6exit("Fishy Error: Can't get path", 2), 127);
	paths = ft_split(getxenv("PATH", msh), ':');
	count = countword(paths);
	pathcmd = malloc((count + 1) * sizeof(char *));
	if (!pathcmd)
		return (1);
	pathcmd[count] = NULL;
	i = -1;
	while (pathcmd[++i] != NULL)
		pathcmd = ft_strjoin(paths[i], cut_point);
	i = -1;
	while (pathcmd[++i] != NULL)
		if (access(pathcmd[i], X_OK) == 0)
			execve(pathcmd[i], cmd, msh->env);
	ft_putstr_fd(cmd[0], 2);
	perror(" ");
	return (xpathfree(paths, pathcmd, cut_point, cmd), 127);
}

static int	child(char **cmd, t_minishell *msh)
{
	if (!cmd)
		return (1);
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
		run(cmd, msh);
	else
		search(cmd, msh);
	exit(127);
}

int	external(char **cmd, t_minishell *msh)
{
	int		status;
	int		value;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (error2exit("Fishy Error: Couldn't fork pid"), 1);
	if (pid == 0)
	{
		value = child(cmd, msh);
		exit(value);
	}
	waitpid(&status, pid, 0);
	if (WIFEXITED(status))
		return (WIFEXITED(status));
	return (1);
}
