/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:20:49 by alechin           #+#    #+#             */
/*   Updated: 2025/07/29 16:23:22 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int	priority(t_token *curr)
{
	int				priority;

	priority = UNDECLARED;
	if (curr->type == TOKEN_WORD
		|| curr->type == TOKEN_PIPE
		|| curr->type == TOKEN_REDIRECT_IN
		|| curr->type == TOKEN_REDIRECT_OUT
		|| curr->type == TOKEN_REDIRECT_APPEND
		|| curr->type == TOKEN_HEREDOC)
		priority = REDIRECTION;
	else if (curr->type == TOKEN_PIPE)
		priority = PIPE;
	else if (!curr->lexer.in_double_quote || !curr->lexer.in_single_quote)
		priority = COMMAND;
	return (priority);
}

bool	determine_level(t_token *tokens, int *level, bool *prev_s, bool *prev_d)
{
	bool	changed;

	changed = false;
	printf("%d\n", (char)tokens->lexer.in_single_quote);
	if (tokens->lexer.in_single_quote != *prev_s)
	{
		if (tokens->lexer.in_single_quote)
			(*level)++;
		else
			(*level)--;
		*prev_s = tokens->lexer.in_single_quote;
		changed = true;
	}
	if (tokens->lexer.in_double_quote != *prev_d)
	{
		if (tokens->lexer.in_double_quote)
			(*level)++;
		else
			(*level)--;
		*prev_d = tokens->lexer.in_double_quote;
		changed = true;
	}
	return (changed);
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

void	reset(t_token **tokens, t_micro *shell)
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
