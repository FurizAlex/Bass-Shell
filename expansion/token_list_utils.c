/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:39:42 by furizalex         #+#    #+#             */
/*   Updated: 2025/08/26 21:37:54 by rpadasia         ###   ########.fr       */
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
