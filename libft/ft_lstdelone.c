/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:35:28 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 12:48:00 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

lstdelone

void ft_lstdelone(t_list *lst, void (*del)(void*));

Description

Takes as a parameter a node and frees the memory of
the node’s content using the function ’del’ given
as a parameter and free the node. The memory of
’next’ must not be freed.

Return Value

it doesn't
*/

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}
/*
#include <stdio.h>

void del(void *ptr)
{
	free(ptr);
}

int	main(void)
{
	t_list *node;
	int *data = malloc(sizeof(int));
	*data = 42;

	node = ft_lstnew(data);

	printf("before; %d\n", ft_lstsize(node));
	ft_lstdelone(node, del);
	node = NULL;
	printf("after; %d\n", ft_lstsize(node));

	return (0);
}*/