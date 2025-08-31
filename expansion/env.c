/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:13:55 by alechin           #+#    #+#             */
/*   Updated: 2025/08/24 19:40:00 by rpadasia         ###   ########.fr       */
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

char	*to_get_env(char *start, int len, t_minishell *msh)
{
	char	*variable_name;
	char	*env_value;

	if (!start || !msh)
		return (NULL);
	variable_name = dupnxtra(start, len);
	if (!variable_name)
		return (NULL);
	env_value = getxenv(variable_name, msh);
	if (!env_value)
		env_value = "";
	free(variable_name);
	return (env_value);
}
