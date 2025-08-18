/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:52:36 by furizalex         #+#    #+#             */
/*   Updated: 2025/08/17 21:15:39 by furizalex        ###   ########.fr       */
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

	curr_level = 0;
	shell->level = INT_MAX;
	curr = ft_tokenlst(*tokens);
	prev_single = 0;
	prev_double = 0;
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

t_token	*operators(t_token **tokens, t_micro *shell, int *priority)
{
	t_token	*cur;
	t_token	*choice;
	int		prio;

	if (!tokens || !*tokens || !shell)
	{
		*priority = COMMAND;
		return (NULL);
	}
	cur = *tokens;
	/* advance to id_start */
	while (cur && cur->id < shell->id_start)
		cur = cur->next;
	choice = NULL;
	prio = COMMAND;
	/* scan from id_start to id_end (inclusive) */
	while (cur && cur->id <= shell->id_end)
	{
		if (cur->id >= shell->id_start && cur->id <= shell->id_end)
		{
			if (cur->type == TOKEN_PIPE)
			{
				choice = cur;
				prio = PIPE;
			}
			else if (redir_type(cur->type) && prio != PIPE)
			{
				choice = cur;
				prio = REDIRECTION;
			}
			else if (cur->type == TOKEN_WORD && prio == COMMAND)
			{
				choice = cur;
			}
		}
		cur = cur->next;
	}
	*priority = prio;
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
		return;
	}
	level(tokens, shell);
	*choice = operators(tokens, shell, &priority);
	temp = *choice;
	while (priority == REDIRECTION && temp)
	{
		temp->is_open = false;
		if (temp->next)
			temp->next->is_open = false;
		temp = operators(tokens, shell, &priority);
		if (!temp)
			break ;
		if (priority == COMMAND)
			*choice = temp;
	}
	reset(tokens, shell);
}
