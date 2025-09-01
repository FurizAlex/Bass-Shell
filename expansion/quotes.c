/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:44:13 by alechin           #+#    #+#             */
/*   Updated: 2025/09/01 16:42:04 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

char	*remove_quotes(char *str)
{
	int		i;
	char	*size;
	char	*temp;
	char	*token;

	i = 0;
	token = ft_strdup("");
	while (str[i])
	{
		size = remove_quotes_size(str, &i);
		temp = ft_strjoin(token, size);
		free(token);
		free(size);
		token = temp;
	}
	return (token);
}

char	*remove_quotes_size(char *str, int *i)
{
	int		start;
	int		end;
	char	quote;
	char	*size;
	int		len;

	quote = 0;
	if (str[*i] == '"' || str[*i] == '\'')
	{
		quote = str[*i];
		(*i)++;
	}
	start = *i;
	end = *i;
	if (!quote)
	{
		while (str[end] && str[end] != '"' && str[end] != '\'')
			end++;
	}
	else
	{
		while (str[end] && str[end] != quote)
			end++;
	}
	len = end - start;
	size = dupnxtra(str + start, len);
	if (quote && str[end] == quote)
		end++;
	*i = end;
	return (size);
}
