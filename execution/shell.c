/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:52:36 by furizalex         #+#    #+#             */
/*   Updated: 2025/08/19 14:10:51 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

void	level(t_token **tokens, t_micro *shell)
{
	t_token	*curr;
	int		curr_level;
	int		prev_single;
	int		prev_double;

	curr = ft_tokenlst(*tokens);
	curr_level = 0;
	prev_single = 0;
	prev_double = 0;
	shell->level = INT_MAX;
	while (curr)
	{
		if (curr->id >= shell->id_start && curr->id <= shell->id_end)
		{
			determine_level(curr, &curr_level, &prev_single, &prev_double);
			if (shell->level > curr_level)
				shell->level = curr_level;
		}
		if (curr->id == shell->id_end || curr_level < 0)
			break ;
		curr = curr->prev;
	}
	if (shell->level == INT_MAX)
		shell->level = 0;
}

static void	update_operator(t_token *last, t_micro *shell,
			t_token **choice, int *priority)
{
	if (*priority == REDIRECTION && *choice)
	{
		(*choice)->is_open = false;
		if ((*choice)->next)
			(*choice)->next->is_open = false;
	}
	if (last->id <= shell->id_start)
		current_order(last, choice, priority);
}

t_token	*operators(t_token **tokens, t_micro *shell, int *priority)
{
	t_token	*last;
	t_token	*choice;
	int		current;

	current = 0;
	choice = NULL;
	*priority = COMMAND;
	last = ft_tokenlst(*tokens);
	while (last)
	{
		if (current == shell->level)
			update_operator(last, shell, &choice, priority);
		if (last->id == shell->id_end)
			break ;
		last = last->prev;
	}
	return (choice);
}

void	splitters(t_token **tokens, t_micro *shell, t_token **choice)
{
	int		priority;
	t_token	*temp;

	if (!tokens || !*tokens)
	{
		fprintf(stderr, "splitters: tokens is NULL\n");
		*choice = NULL;
		return ;
	}
	level(tokens, shell);
	*choice = operators(tokens, shell, &priority);
	temp = *choice;
	while (priority == REDIRECTION && temp)
	{
		update_operator(temp, shell, &temp, &priority);
		if (!temp)
			break ;
		if (priority == COMMAND)
			*choice = temp;
	}
	reset(tokens, shell);
}
