/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:35:47 by furizalex         #+#    #+#             */
/*   Updated: 2025/09/01 17:42:19 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	search_path_loop(char **paths, char *cut, char **cmd)
{
	int			i;
	char		*candidate;
	t_minishell	*msh;

	i = 0;
	msh = minishell();
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
}
