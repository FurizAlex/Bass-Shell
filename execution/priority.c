/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:20:49 by alechin           #+#    #+#             */
/*   Updated: 2025/07/11 18:00:03 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	priority(t_token *curr)
{
	int		priority;
	t_token	type;
	t_token	lex;

	lex = curr->lexer;
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

void	current_order(t_token *curr, t_token **choice, int *priority)
{
	int	order;

	order = priority(curr);
	if (order == TOKEN_PIPE)
	{
		if (*priority != TOKEN_PIPE)
		{
			priority = PIPE;
			*choice = curr;
		}
		return ;
	}
	if (order == REDIRECTION
		&& *priority != PIPE
		&& *priority != COMMAND)
	{
		priority = REDIRECTION;
		*choice = curr;
		return ;
	}
	if (order == COMMAND
		&& *priority != PIPE
		&& *priority != REDIRECTION)
		*choice = curr;
}

t_token	*find_position(t_token **tokens, int id)
{
	t_token	*search;

	find = ft_lstlast(tokens);
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
