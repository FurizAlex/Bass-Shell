/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:47:52 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 12:39:14 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

lstadd_front

void ft_lstadd_front(t_list **lst, t_list *new);

Description

Adds the node ’new’ at the beginning of the list.

Return Value

it doesn't
*/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>
int	main(void)
{
	int data = 21; int data2 = 72;
	
	t_list *start = ft_lstnew(&data);

	ft_lstadd_front(&start, ft_lstnew(&data2));
	printf("%d\n", *(int *)start->content);

	return (0);
}*/