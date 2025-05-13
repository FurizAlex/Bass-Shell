/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:50:07 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 12:49:01 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

lstiter

void ft_lstiter(t_list *lst, void (*f)(void *));

Description

Iterates the list ’lst’ and applies the function
’f’ on the content of each node.

Return Value

it doesn't
*/

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst ->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>

void example(void *ptr)
{
	printf("%d\n", *(int *)ptr);
}

int main(void)
{
    int *data1 = malloc(sizeof(int));
	int *data2 = malloc(sizeof(int));
	int *data3 = malloc(sizeof(int));

    *data1 = 23; *data2 = 58; *data3 = 62;

	t_list *start = ft_lstnew(data1);
    ft_lstadd_back(&start, ft_lstnew(data2));
    ft_lstadd_back(&start, ft_lstnew(data3));
	ft_lstiter(start, example);

    return (0);
}*/