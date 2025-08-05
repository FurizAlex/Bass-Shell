/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:59:31 by alechin           #+#    #+#             */
/*   Updated: 2025/08/05 17:27:01 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int	box_length(t_token *token)
{
	int	length;

	length = 0;
	while (token)
	{
		if (priority(token) == COMMAND)
		{
			length++;
			token = token->next;
		}
		else
		{
			if (length != 0)
				break ;
			else if (priority(token) == PIPE)
				return (1);
			else
				return (2);
		}
	}
	return (length);
}

bool	out_of_bounds(t_token *token, t_micro shell, bool outbox)
{
	int		i;
	t_token	*curr;

	i = -1;
	curr = token;
	while (curr)
	{
		if (curr->id <= shell.id_start
			&& curr->id >= shell.id_end)
		{
			i++;
			if (outbox)
				curr = curr->next;
			else
				curr = curr->prev;
		}
		else
			break ;
	}
	if ((i >= shell.length && outbox) || (i >= 1 && !outbox))
		return (true);
	return (false);
}

t_micro	micro_editor(t_micro shell, t_token *token, bool right)
{
	t_micro	microshell;

	microshell = shell;
	if (right)
		microshell.id_end = token->id + shell.length;
	else
		microshell.id_end = token->id - 1;
	return (microshell);
}

int	recursive_tree(t_root **root, t_micro shell, t_token **token, bool right)
{
	t_token	*tokens;
	t_root	*new_root;

	splitters(token, &shell, &tokens);
	new_root = new(root, tokens, shell);
	if (!new_root)
		return (MEMORY);
	shell.err = insertation(root, &new_root, right);
	if (out_of_bounds(tokens, shell, false))
		shell.err = recursive_tree(root, micro_editor(shell, tokens, false),
				token, false);
	if (shell.err != UNDECLARED)
		return (shell.err);
	if (out_of_bounds(tokens, shell, true))
		shell.err = recursive_tree(root, micro_editor(shell, tokens, true),
				token, true);
	return (shell.err);
}

int	ast(t_root **root, t_token **tokens)
{
	int				err;
	t_micro			shell;

	*root = NULL;
	shell.id_end = 0;
	shell.id_start = (*tokens)->id;
	err = recursive_tree(root, shell, tokens, true);
	if (err == MEMORY)
		ft_putstr_fd("\x1b[0;31mError: Malloc\x1b[0m\n", 2);
	else if (err == REDIRECTION)
		ft_putstr_fd("\x1b[0;31mError: Incorrect Redirect Use\x1b[0m\n", 2);
	else if (err == PIPE)
		ft_putstr_fd("\x1b[0;31mError: Incorrect Pipe Use\x1b[0m\n", 2);
	return (err);
}
