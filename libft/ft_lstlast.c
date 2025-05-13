/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:33:17 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 12:50:49 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

lstlast

t_list *ft_lstlast(t_list *lst);

Description

Returns the last node of the list.

Return Value

Last node of the list
*/

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
	{
		return (NULL);
	}
	while (lst->next)
	{
		lst = (lst->next);
	}
	return (lst);
}
/*
#include <stdio.h>
int	main(void)
{
	int data = 61; int data2 = 193; int data3 = 132;
	t_list *start = ft_lstnew(&data);

	ft_lstadd_back(&start, ft_lstnew(&data2));
	ft_lstadd_back(&start, ft_lstnew(&data3));
	printf("%d\n", *(int *)ft_lstlast(start)->content);
	
	return (0);
}*/