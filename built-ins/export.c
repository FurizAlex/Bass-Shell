/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:29 by alechin           #+#    #+#             */
/*   Updated: 2025/06/19 10:55:02 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	arch_key(t_env *env)
{
	int	i;
	
	i = -1;
	if (!env->key || ft_strchr("1234567890", env->key[0]) != NULL)
	{
		/* throw an error and exit status should be 1 */
		return (0);
	}
	while (env->key[++i])
	{
		if (ft_strchr("!@#$%^&()_+{}|:\"<>?`~-=[]\\;',./", env->key[i]) != NULL)
		{
			/* throw an error and exit status should be 1 */
			return (0);
		}
	}
	return (1);
}