/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:20:29 by alechin           #+#    #+#             */
/*   Updated: 2025/08/07 17:42:01 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

void	terminate_ast(t_root **root)
{
	t_root	*left;
	t_root	*right;

	if (!root || !*root)
		return ;
	left = (*root)->left;
	right = (*root)->right;
	if (left)
		terminate_ast(&left);
	if (right)
		terminate_ast(&right);
	if ((*root)->tokens)
		free((*root)->tokens);
	free(*root);
}

void	terminate_tokens(t_token **tokens)
{
	t_token	*current;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		*tokens = (*tokens)->next;
		if (current->value)
			free(current->value);
		free(current);
		current = *tokens;
	}
}
