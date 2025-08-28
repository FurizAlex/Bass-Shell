/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:59:31 by alechin           #+#    #+#             */
/*   Updated: 2025/08/24 19:59:51 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

// int	box_length(t_token *token)
// {
// 	int	length;

// 	length = 0;
// 	while (token)
// 	{
// 		if (priority(token) == COMMAND)
// 		{
// 			length++;
// 			token = token->next;
// 		}
// 		else
// 		{
// 			if (length != 0)
// 				break ;
// 			else if (priority(token) == PIPE)
// 				return (1);
// 			else
// 				return (2);
// 		}
// 	}
// 	return (length);
// }

// bool	out_of_bounds(t_token *token, t_micro shell, bool outbox)
// {
// 	int		i;
// 	t_token	*curr;

// 	i = -1;
// 	curr = token;
// 	while (curr)
// 	{
// 		if (curr->id >= shell.id_start
// 			&& curr->id <= shell.id_end)
// 		{
// 			i++;
// 			if (outbox)
// 				curr = curr->next;
// 			else
// 				curr = curr->prev;
// 		}
// 		else
// 			break ;
// 	}
// 	if ((i >= shell.length && outbox) || (i >= 1 && !outbox))
// 		return (true);
// 	return (false);
// }

// t_micro	micro_editor(t_micro shell, t_token *token, bool right)
// {
// 	t_micro	microshell;

// 	microshell = shell;
// 	if (right)
// 		microshell.id_end = token->id + shell.length;
// 	else
// 		microshell.id_end = token->id - 1;
// 	return (microshell);
// }

// int	recursive_tree(t_root **root, t_micro shell, t_token **token, bool right)
// {
// 	t_root	*new_root;
// 	int		err;

// 	new_root = new(root, *token, shell);
// 	if (!new_root)
// 		return (MEMORY);
// 	err = insertation(root, &new_root, right);
// 	if (err != UNDECLARED)
// 		return (err);
// 	if (out_of_bounds(new_root->tokens[0], shell, false))
// 	{
// 		err = recursive_tree(root, micro_editor(shell, new_root->tokens[0], false),
// 				token, false);
// 		if (err != UNDECLARED)
// 			return (err);
// 	}
// 	if (out_of_bounds(new_root->tokens[0], shell, true))
// 	{
// 		err = recursive_tree(root, micro_editor(shell, new_root->tokens[0], true),
// 				token, true);
// 		if (err != UNDECLARED)
// 			return (err);
// 	}
// 	return (UNDECLARED);
// }

// int	ast(t_root **root, t_token **tokens)
// {
// 	int				err;
// 	t_micro			shell;

// 	*root = NULL;
// 	if (!tokens || !*tokens)
// 		return (UNDECLARED);
// 	shell.id_start = (*tokens)->id;
// 	shell.id_end = ft_tokenlst(*tokens)->id;
// 	shell.length = 0;
// 	t_token *temp = *tokens;
// 	while (temp)
// 	{
// 		shell.length++;
// 		temp = temp->next;
// 	}
// 	*root = create_initial_root(tokens, &shell);
// 	err = recursive_tree(root, shell, tokens, true);
// 	if (err == MEMORY)
// 		ft_putstr_fd("\x1b[0;31mError: Malloc\x1b[0m\n", 2);
// 	else if (err == REDIRECTION)
// 		ft_putstr_fd("\x1b[0;31mError: Incorrect Redirect Use\x1b[0m\n", 2);
// 	else if (err == PIPE)
// 		ft_putstr_fd("\x1b[0;31mError: Incorrect Pipe Use\x1b[0m\n", 2);
// 	return (err);
// }
