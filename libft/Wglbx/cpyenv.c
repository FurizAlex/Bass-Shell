/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpyenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:33:43 by alechin           #+#    #+#             */
/*   Updated: 2025/07/10 12:43:57 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wglbx.h"

char	**cpyenv(char **env)
{
	int		i;
	int		num_o_str;
	char	**envp;

	i = 0;
	num_o_str = countword(env);
	envp = malloc((num_o_str + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	while (env[i] != NULL)
	{
		envp[i] = ft_strdup(env[i]);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
