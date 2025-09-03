/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getxenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:33:17 by alechin           #+#    #+#             */
/*   Updated: 2025/07/10 12:03:15 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wglbx.h"

char	*getxenv(char *name, t_minishell *e)
{
	int		i;
	int		len;
	char	*envp;

	i = 0;
	len = measure(name);
	while (e->env[i])
	{
		envp = e->env[i];
		if (!(ncomp(&envp[i], name, len) > 0) && envp[len] == '=')
			return (&envp[len + 1]);
		i++;
	}
	return (NULL);
}
