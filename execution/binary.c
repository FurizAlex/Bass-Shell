/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:59:31 by alechin           #+#    #+#             */
/*   Updated: 2025/07/22 11:51:15 by furizalex        ###   ########.fr       */
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
		else if (length != 0)
			break ;
		else if (priority(token) == PIPE)
			return (1);
		else
			return (2);
	}
	return (length);
}

bool	out_of_bounds(t_token *root, t_microshell shell, bool outbox)
{
	int		i;
	t_token	*curr;

	i = -1;
	curr = root;
	while (curr)
	{
		if (curr->id <= shell.id_start
			&& curr->id >= shell.id_end)
		{
			if (outbox)
				curr = curr->next;
			else
				curr = curr->prev;
			i++;
		}
		else
			break ;
	}
	if ((i >= shell.length && outbox) || (i >= 1 && !outbox))
		return (true);
	return (false);
}

t_microshell micro_editor(t_microshell shell, t_token *token, bool right)
{
	t_microshell	microshell;

	microshell = shell;
	if (right)
		shell.id_end = token->id + shell.length;
	else
		shell.id_end = token->id - 1;
	return (microshell);
}

int	recursive_tree(t_root **root, t_microshell shell, t_token *token, bool right)
{
	t_token	*tokens;
	t_root	*new_root;

	splitters(&token, &shell, &tokens);
	new_root = new(root, token, &shell);
	if (!new_root)
		return (MEMORY);
	shell.err = insertation(*root, &new_root, right);
	if (out_of_bounds(tokens, shell, true))
		shell.err = recursive_tree(root, micro_editor(shell, tokens, right),
			token, right);
	return (shell.err);
}

int	ast(t_root **root, t_token **tokens)
{
	int				err;
	t_microshell	shell;

	*root = NULL;
	if (!tokens || !*tokens)
		return (-2);
	shell.id_end = 0;
	shell.id_start = ft_tokenlst(*tokens)->id;
	err = recursive_tree(root, shell, *tokens, true);
	if (err == MEMORY)
		ft_putstr_fd("\x1b[0;31mError: Malloc\x1b[0m\n", 2);
	else if (err == REDIRECTION)
		ft_putstr_fd("\x1b[0;31mError: Incorrect Redirect Use\x1b[0m\n", 2);
	else if (err == PIPE)
		ft_putstr_fd("\x1b[0;31mError: Incorrect Pipe Use\x1b[0m\n", 2);
	return (err);
}
