/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:12:03 by furizalex         #+#    #+#             */
/*   Updated: 2025/08/13 17:12:37 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

char	*join_free_both(char *a, char *b)
{
	char	*r;

	if (!a || !b)
	{
		free(a);
		free(b);
		return (NULL);
	}
	r = ft_strjoin(a, b);
	free(a);
	free(b);
	return (r);
}

char	*join_free_first(char *a, char *b)
{
	char	*r;

	if (!a || !b)
	{
		free(a);
		return (NULL);
	}
	r = ft_strjoin(a, b);
	free(a);
	return (r);
}