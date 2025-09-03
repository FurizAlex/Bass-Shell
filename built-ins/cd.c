/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:19 by alechin           #+#    #+#             */
/*   Updated: 2025/09/03 10:18:59 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

static int	arg_count(char **cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

static void	update_pwd_vars(t_minishell *e, char *oldpwd)
{
	export_pwd_var(e, "OLDPWD=", oldpwd);
	if (getxenv("PWD", e) != NULL)
	{
		if (getcwd(oldpwd, 4096))
			export_pwd_var(e, "PWD=", oldpwd);
	}
}

static char	*get_target(char **cmd, t_minishell *e)
{
	if (!cmd[1] || ft_strlen(cmd[1]) == 0)
		return (getxenv("HOME", e));
	if (ft_strncmp(cmd[1], "-", 2) == 0)
		return (getxenv("OLDPWD", e));
	return (cmd[1]);
}

static int	check_args(char **cmd)
{
	if (arg_count(cmd) > 2)
	{
		error2exit("Fishy Warning: Too many arguments", 1);
		return (1);
	}
	return (0);
}

int	koi_cd(char **cmd, t_minishell *e)
{
	char	oldpwd[4096];
	char	newpwd[4096];
	char	*target;

	if (check_args(cmd))
		return (1);
	if (!getcwd(oldpwd, sizeof(oldpwd)))
		return (error2exit("Fishy Error: Couldn't get cwd", 1), 1);
	target = get_target(cmd, e);
	if (!target)
		return (error6exit("Fishy Error: Target not set", 1), 1);
	if (chdir(target) != 0)
	{
		ft_putstr_fd("Fishy Error: Can't change directory\n", 2);
		perror("chdir");
		return (1);
	}
	update_pwd_vars(e, oldpwd);
	if (!getcwd(newpwd, sizeof(newpwd)))
		return (error2exit("Fishy Error: Couldn't get new cwd", 1), 1);
	(void)newpwd;
	return (0);
}
