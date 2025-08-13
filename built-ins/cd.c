/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:19 by alechin           #+#    #+#             */
/*   Updated: 2025/08/11 16:41:10 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

static int arg_count(char **cmd)
{
	int i;
	int count;

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
	char	*joined;
	char	*variables;

	joined = ft_strjoin("OLDPWD=", oldpwd);
	variables = ft_strdup(joined);
	if (!joined)
	{
		koi_export(e, &variables);
		free(joined);
	}
	if (getxenv("PWD", e) != NULL)
	{
		if (!getcwd(oldpwd, 4096))
		{
			joined = ft_strjoin("OLDPWD=", oldpwd);
			if (!joined)
			{
				koi_export(e, &variables);
				free(joined);
			}
		}
	}
}

int	koi_cd(char **cmd, t_minishell *e)
{
	char oldpwd[4096];
	char newpwd[4096];
	char *target;

	if (arg_count(cmd) > 2)
	{
		error2exit("Fishy Warning: Too many arguments", 1);
		return (1);
	}
	if (!getcwd(oldpwd, sizeof(oldpwd)))
		return (error2exit("Fishy Error: Couldn't get current directory", 1), 1);
	if (!cmd[1] || ft_strlen(cmd[1]) == 0)
		target = getxenv("HOME", e);
	else if (ft_strncmp(cmd[1], "-", 2) == 0)
		target = getxenv("OLDPWD", e);
	else
		target = cmd[1];
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
