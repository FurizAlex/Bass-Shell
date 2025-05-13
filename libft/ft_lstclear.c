/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:40:24 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 12:42:37 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

lstclear

void ft_lstclear(t_list **lst, void (*del)(void*));

Description

Deletes and frees the given node and every
successor of that node, using the function ’del’
and free(3).
Finally, the pointer to the list must be set to
NULL.

Return Value

it doesn't
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = next;
	}
	*lst = NULL;
}
/*
#include <stdio.h>

void del(void *ptr)
{
	free(ptr);
}

int	main(void)
{
	t_list *start;
	int *data = malloc(sizeof(int)); int *data2 = malloc(sizeof(int));
	*data = 10; *data = 25;

	start = ft_lstnew(data);
	
	ft_lstadd_back(&start, ft_lstnew(data2));
	printf("before; %d\n", ft_lstsize(start));
	ft_lstclear(&start, del);
	printf("after; %d\n", ft_lstsize(start));

	return (0);
}*/