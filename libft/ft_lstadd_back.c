/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:41:46 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 12:38:04 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

lstadd_back

void ft_lstadd_back(t_list **lst, t_list *new)

Description

Adds the node ’new’ at the end of the list.

Return Value

it doesn't
*/

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}
/*
#include <stdio.h>
int	main(void)
{
	int data = 21; int data2 = 72;
	
	t_list *start = ft_lstnew(&data);

	ft_lstadd_back(&start, ft_lstnew(&data2));
	printf("%d\n", *(int *)start->content);

	return (0);
}*/