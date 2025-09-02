/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:39:42 by furizalex         #+#    #+#             */
/*   Updated: 2025/09/02 10:41:44 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	set_token_prev_pointers(t_token *head)
{
	t_token	*current;
	t_token	*prev_token;

	current = head;
	prev_token = NULL;
	while (current)
	{
		current->prev = prev_token;
		prev_token = current;
		current = current->next;
	}
}

void	check_quotes_in_value(char *value, bool *s_q, bool *d_q)
{
	int	i;

	i = 0;
	*s_q = false;
	*d_q = false;
	if (!value)
		return ;
	while (value[i])
	{
		if (value[i] == '\'')
			*s_q = !(*s_q);
		else if (value[i] == '"')
			*d_q = !(*d_q);
		i++;
	}
}

int	handle_quote(char *str, int *i, char quote)
{
	int	end;

	end = *i;
	while (str[end] && str[end] != quote)
		end++;
	if (str[end] == quote)
		end++;
	return (end);
}

int	handle_no_quote(char *str, int *i)
{
	int	end;

	end = *i;
	while (str[end] && str[end] != '\'' && str[end] != '"')
		end++;
	return (end);
}

int	is_valid_identifier(char *s)
{
	int	i;

	if (!s || (!ft_isalpha((unsigned char)s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum((unsigned char)s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
