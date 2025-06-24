/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:13:55 by alechin           #+#    #+#             */
/*   Updated: 2025/06/24 10:46:44 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int	variable_len(char *start)
{
	int		len;
	char	*pointer;

	len = 0;
	pointer = start;
	while (*pointer && valid_env_ch(*pointer))
	{
		len++;
		pointer++;
	}
	return (len);
}

char	*to_get_env(char *start, int len, t_root *root)
{
	char	*variable_name;
	char	*env_value;

	variable_name = ft_strdup(start, len);
	env_value = getxenv(variable_name, root);
	if (!variable_name)
		return (NULL);
	if (!env_value)
		env = "";
	free(variable_name);
	return (env_value);
}