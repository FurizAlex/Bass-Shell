/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:20:29 by alechin           #+#    #+#             */
/*   Updated: 2025/06/24 17:34:25 by alechin          ###   ########.fr       */
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

	current = *tokens;
	if (!tokens || !*tokens)
		return ;
	while (current)
	{
		*tokens = (*tokens)->next;
		if (current->value)
			free(current->value);
		free(current);
		current = *tokens;
	}
}