/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:20:49 by alechin           #+#    #+#             */
/*   Updated: 2025/07/22 10:40:14 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int	priority(t_token *curr)
{
	int				priority;
	t_token_type	type;

	type = curr->type;
	priority = UNDECLARED;
	if (type == TOKEN_WORD
		|| type == TOKEN_PIPE
		|| type == TOKEN_REDIRECT_IN
		|| type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_REDIRECT_APPEND
		|| type == TOKEN_HEREDOC)
		priority = REDIRECTION;
	else if (type == TOKEN_PIPE)
		priority = PIPE;
	else if (!curr->lexer.in_double_quote || !curr->lexer.in_single_quote)
		priority = COMMAND;
	return (priority);
}

void	current_order(t_token *curr, t_token **choice, int *prior)
{
	int	order;

	order = priority(curr);
	if (order == PIPE)
	{
		if (*prior != PIPE)
		{
			*prior = PIPE;
			*choice = curr;
		}
		return ;
	}
	if (order == REDIRECTION
		&& *prior != PIPE
		&& *prior != COMMAND)
	{
		*prior = REDIRECTION;
		*choice = curr;
		return ;
	}
	if (order == COMMAND
		&& *prior != PIPE
		&& *prior != REDIRECTION)
		*choice = curr;
}

t_token	*find_position(t_token **tokens, int id)
{
	t_token	*search;

	search = ft_tokenlst(*tokens);
	while (search)
	{
		if (search->id == id)
			break ;
		search = search->next;
	}
	return (search);
}

void	reset(t_token **tokens, t_microshell *shell)
{
	t_token	*curr;

	curr = find_position(tokens, shell->id_start);
	while (curr)
	{
		curr->is_open = true;
		if (curr->id == shell->id_end)
			break ;
		curr = curr->next;
	}
}
