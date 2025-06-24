/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:52:13 by alechin           #+#    #+#             */
/*   Updated: 2025/06/24 10:21:16 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

char	*invalid(char *dollar, t_root *root)
{
	/* todo!() */
}

char	*valid(char *dollar, t_root *root)
{
	/* todo!() */
}

char	question_mark(char	*dollar, t_root *root)
{
	/* todo!() */
}

char	*expand_dollar(char *dollar, t_root *root)
{
	int		i;
	bool	is_valid;

	i = 0;
	is_valid = false;
	if (dollar[i] == '$')
	{
		/* todo!() */
	}
	return (dollar);
}