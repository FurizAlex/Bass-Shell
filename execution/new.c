/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:01:10 by alechin           #+#    #+#             */
/*   Updated: 2025/08/06 17:37:31 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

static void	*reallocation(void *start, size_t original, size_t size, size_t count)
{
    void *new_point;

    if (count == 0)
    {
        free(start);
        return NULL;
    }
    new_point = malloc(count * size);
    if (!new_point)
        return NULL;
    if (start)
    {
        if (original > count)
            original = count;
        ft_memcpy(new_point, start, size * original);
        free(start);
    }
    return new_point;
}

bool	set(t_root **root, t_token *curr, int list)
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
	if (priority(curr) == 1 && priority(temp->tokens[0]) == 1)
	{
		i = -1;
		while (temp->tokens[i])
			++i;
		num = i + list;
		temp->tokens = reallocation(temp->tokens, i, sizeof(t_token *), num + 1);
		while (i < num && curr)
		{
			temp->tokens[i++] = curr;
			curr = curr->next;
		}
		temp->tokens[num] = NULL;
		return (true);
	}
	return (false);
}

t_root	*new(t_root **root, t_token *token, t_micro shell)
{
	int		i;
	t_root	*new;

	(void)root;
	new = calloc(1, sizeof(t_root));
	if (!new)
		return (NULL);
	new->tokens = ft_calloc(shell.length + 1, sizeof(t_token *));
	if (!new->tokens)
	{
		free(new);
		return (NULL);
	}
	i = -1;
	while (++i < shell.length)
	{
		if (!token)
			break ;
		new->tokens[i] = token;
		token = token->next;
	}
	new->tokens[i] = NULL;
	new->origin = NULL;
	new->left = NULL;
	new->right = NULL;
	new->level = shell.level;
	new->msh = minishell();
	return (new);
}

int insertation(t_root **root, t_root **new, bool right)
{
    if (!new || !*new)
		return (UNDECLARED);
	if (root && *root)
	{
		(*new)->origin = *root;
		if (right)
			(*root)->right = *new;
		else
			(*root)->left = *new;
	}
	return (heredoc_checker(new));
}
