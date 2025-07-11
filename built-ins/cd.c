/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:19 by alechin           #+#    #+#             */
/*   Updated: 2025/07/10 13:41:41 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	home(t_minishell *e)
{
	char		*home;

	home = getxenv("HOME", e);
	if (chdir(home) != 0)
		error6exit("Fishy Error: Home isn't set", 2);
	return (0);
}

int	prev(t_minishell *e)
{
	char		*old_dir;

	old_dir = getxenv("OLDPWD", e);
	if (chdir(old_dir) != 0)
		error6exit("Fishy Error: Old directory not set", 2);
	ft_printf("%s\n", old_dir);
	return (0);
}

int	change_directory(char **cmd, t_minishell *e)
{
	int	decider;

	decider = 0;
	if (ft_strncmp(cmd[1], ".", 3) == 0 || cmd[1] == NULL)
		decider = home(e);
	else if (ft_strncmp(cmd[1], "..", 2) == 0)
		decider = prev(e);
	else if (chdir(cmd[1]) != 0)
	{
		free(cmd);
		ft_putstr_fd("Fishy Error: Can't change directory\n", 1);
		perror(" ");
		return (1);
	}
	return (decider);
}

int	koi_cd(char **cmd, t_minishell *e)
{
	char	buffer[4096];
	char	*old_dir;
	char	*current_dir;
	int		return_value;

	old_dir = ft_strjoin("OLDPWD=", buffer);
	return_value = change_directory(cmd, e);
	if (countword(cmd) >= 3)
		error2exit("Fishy Warning: Too many arguments", 1);
	if (!getcwd(buffer, 4096))
		error2exit("Fishy Error: Couldn't get current directory", 1);
	if (return_value != 0)
		return (return_value);
	e->env = koi_export(old_dir, e);
	current_dir = ft_strjoin("PWD=", buffer);
	e->env = koi_export(current_dir, e);
	free(old_dir);
	free(current_dir);
	return (0);
}
