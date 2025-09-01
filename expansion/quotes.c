/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:44:13 by alechin           #+#    #+#             */
/*   Updated: 2025/09/01 17:26:19 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

static int	find_end_unquoted(char *str, int start)
{
	while (str[start] && str[start] != '"' && str[start] != '\'')
		start++;
	return (start);
}

static int	find_end_quoted(char *str, int start, char quote)
{
	while (str[start] && str[start] != quote)
		start++;
	return (start);
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
		quote = str[(*i)++];
	start = *i;
	if (!quote)
		end = find_end_unquoted(str, *i);
	else
		end = find_end_quoted(str, *i, quote);
	len = end - start;
	size = dupnxtra(str + start, len);
	if (quote && str[end] == quote)
		end++;
	*i = end;
	return (size);
}

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
