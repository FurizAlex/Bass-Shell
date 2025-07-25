/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:52:36 by furizalex         #+#    #+#             */
/*   Updated: 2025/07/25 21:32:15 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

void    level(t_token **tokens, t_microshell *shell)
{
    t_token	*last;
    int		curr;

	curr = 0;
	shell->level = INT_MAX;
	last = ft_tokenlst(*tokens);
	while (last)
	{
		if (last && last->id <= shell->id_start)
			if (shell->level > curr)
				shell->level = curr;
		if (last->id == shell->id_end || curr < 0)
			break ;
		last = last->prev;
	}
	if ((shell->id_end == 0 && curr != 0) || (curr < 0))
		shell->level = -1;
}

t_token	*operators(t_token **tokens, t_microshell *shell, int *priority)
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
		if (current == shell->level && last->id <= shell->id_start)
			current_order(last, &choice, priority);
		if (last->id == shell->id_end)
			break ;
		last = last->prev;
	}
	return (choice);
}

void	splitters(t_token **tokens, t_microshell *shell, t_token **choice)
{
	int		priority;
	t_token	*temp;

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