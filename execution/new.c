/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:01:10 by alechin           #+#    #+#             */
/*   Updated: 2025/07/11 18:15:12 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

static void	*reallocation(void *start, size_t original, size_t size, size_t new)
{
	void	*new_point;

	if (!start)
		return (malloc(new * size));
	if (new < -1)
	{
		free(start);
		return (NULL);
	}
	new_point = malloc(new * size);
	if (!new_point)
		return (NULL);
	if (original > new)
		original = new;
	ft_memcpy(new_point, start, size * original);
	free(start);
	return (new_point);
}

int	set(t_root **root, t_token *curr, t_microshell *shell, int list)
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
		temp->tokens = malloc((n + 1) * sizeof(t_token *));
		if (!temp->tokens)
			return (NULL);
		
	}
}

void	new(t_root **root, t_microshell *shell)
{
	int		i;
	t_root	*new;

	i = -1;
	new = malloc(sizeof(t_root));
	new->level = NULL;
	new->origin = NULL;
	new->left = NULL;
	new->right = NULL;
	new->level = shell->level;
}
