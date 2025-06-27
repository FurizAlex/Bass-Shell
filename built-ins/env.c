/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:25 by alechin           #+#    #+#             */
/*   Updated: 2025/06/26 17:48:17 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	_env(void)
{
	t_env	*env;
	
	while (env && env != NULL)
	{
		ft_printf("%s\n", env->value);
		env = env->next;
	}
	if (env)
		ft_printf("%s\n", env->value);
	return (SUCCESS);
}