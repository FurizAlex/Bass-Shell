/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:12:03 by furizalex         #+#    #+#             */
/*   Updated: 2025/09/01 16:02:21 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

bool	is_single_quoted_literal(char *s)
{
	size_t len;

	if (!s)
		return (false);
	len = ft_strlen(s);
	if (len >= 2 && s[0] == '\'' && s[len - 1] == '\'')
		return (true);
	return (false);
}

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