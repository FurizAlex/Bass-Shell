/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:46:19 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 13:05:22 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

ft_lstnew

t_list *ft_lstnew(void *content);

Description

Allocates (with malloc(3)) and returns a new node.
The member variable ’content’ is initialized with
the value of the parameter ’content’. The variable
’next’ is initialized to NULL

Return Value

The new node
*/

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
	{
		return (NULL);
	}
	node -> content = content;
	node -> next = NULL;
	return (node);
}
/*
#include <stdio.h>
int	main(void)
{
	int data = 101; t_list *start = ft_lstnew(&data);
	printf("%dn\n", *(int *)start->content);
	
	return (0);
}*/