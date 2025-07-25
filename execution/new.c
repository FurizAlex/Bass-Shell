/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:01:10 by alechin           #+#    #+#             */
/*   Updated: 2025/07/25 21:38:24 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

static void	*reallocation(void *start, size_t original, size_t size, size_t new)
{
	void	*new_point;

	if (new == 0)
	{
		free(start);
		return (NULL);
	}
	new_point = malloc(new * size);
	if (!new_point)
		return (NULL);
	if (start)
	{
		if (original > new)
			original = new;
		ft_memcpy(new_point, start, size * original);
		free(start);
	}
	return (new_point);
}

int	set(t_root **root, t_token *curr, int list)
{
	int		i;
	int		num;
	t_root	*temp;

	i = 0;
	num = 0;
	temp = *root;
	while (temp->origin)
		if (!temp->tokens)
			temp = temp->origin;
	if (priority(curr) == 1
		&& priority(temp->tokens[0]) == 1)
	{
		i = -1;
		while (temp->tokens[i])
			++i;
		num = i + list;
		temp->tokens = reallocation(curr, i, num + 1, sizeof(t_token *));
		if (!temp->tokens)
			return (1);
		while (i < num && curr)
		{
			temp->tokens[i++] = curr;
			curr = curr->next;
		}
		temp->tokens[num] = NULL;
		return (0);
	}
	return (1);
}

void	*new(t_root **root, t_token *token, t_microshell *shell)
{
	int		i;
	t_root	*new;

	i = -1;
	new = malloc(sizeof(t_root));
	new->tokens = NULL;
	new->origin = NULL;
	new->left = NULL;
	new->right = NULL;
	new->level = shell->level;
	if (*root && set(root, *new->tokens, shell->length))
		return (new);
	new->tokens = malloc(sizeof(t_token *) * shell->length + 1);
	if (!new || !new->tokens)
		return (NULL);
	while (i++ < shell->length)
	{
		if (!token)
			break ;
		new->tokens[i] = token;
		token = token->next;
	}
	new->tokens[i] = NULL;
	return (new);
}

int insertation(t_root *root, t_root **new, bool right)
{
	if (!*new)
		return (UNDECLARED);
	if (!root)
		root = *new;
	if (root)
	{
		(*new)->origin = root;
		if (right)
			root->right = *new;
		else
			root->left = *new;
	}
	return (UNDECLARED);
}
