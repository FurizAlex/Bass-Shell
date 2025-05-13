/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:18:39 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 14:01:08 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

ft_lstsize

int ft_lstsize(t_list *lst);

Description

Counts the number of nodes in a list.

Return Value

The length of the list
*/

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*
#include <stdio.h>
int	main(void)
{
	int data = 40; int data2 = 12; int data3 = 81;
	t_list *start = ft_lstnew(&data);

	ft_lstadd_back(&start, ft_lstnew(&data2));
	ft_lstadd_back(&start, ft_lstnew(&data3));

	printf("%d\n", ft_lstsize(start));

	return (0);
}*/