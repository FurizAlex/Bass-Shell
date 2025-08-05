/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:20:49 by alechin           #+#    #+#             */
/*   Updated: 2025/08/05 16:46:28 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int	priority(t_token *curr)
{
	if (!curr || !curr->lexer)
		return (UNDECLARED);
	if (curr->type == TOKEN_WORD
		|| curr->type == TOKEN_PIPE
		|| curr->type == TOKEN_REDIRECT_IN
		|| curr->type == TOKEN_REDIRECT_OUT
		|| curr->type == TOKEN_REDIRECT_APPEND
		|| curr->type == TOKEN_HEREDOC)
		return (REDIRECTION);
	else if (curr->type == TOKEN_PIPE)
		return (PIPE);
	else if (!curr->lexer->in_double_quote || !curr->lexer->in_single_quote)
		return (COMMAND);
	return (UNDECLARED);
}

int	determine_level(t_token *tokens, int *level, int *prev_s, int *prev_d)
{
	bool	curr_in_single;
	bool	curr_in_double;

	check_quotes_in_value(tokens->value,
		&curr_in_single, &curr_in_double);
	if (tokens->lexer->in_single_quote != *prev_s)
		*level += 1;
	if (tokens->lexer->in_single_quote != *prev_d)
		*level += 2;
	*prev_s = tokens->lexer->in_single_quote;
	*prev_d = tokens->lexer->in_double_quote;
	return (0);
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

	search = *tokens;
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
