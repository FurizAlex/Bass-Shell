/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:25 by alechin           #+#    #+#             */
/*   Updated: 2025/09/01 16:47:47 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	koi_env(t_minishell *e)
{
	int		i;
	char	*eq;

	i = 0;
	while (e->env[i])
	{
		eq = ft_strchr(e->env[i], '=');
		if (eq && *(eq + 1))
			printf("%s\n", e->env[i]);
		i++;
	}
	return (0);
}
