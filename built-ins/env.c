/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:25 by alechin           #+#    #+#             */
/*   Updated: 2025/06/30 17:18:46 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	koi_env(void)
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
