/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:57:41 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 12:55:29 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

lstmap

t_list *ft_lstmap(t_list *lst, void *(*f)(void *),
void (*del)(void *));

Description

Iterates the list ’lst’ and applies the function
’f’ on the content of each node. Creates a new
list resulting of the successive applications of
the function ’f’. The ’del’ function is used to
delete the content of a node if needed

Return Value

The new list.
NULL if the allocation fails
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;

	head = NULL;
	if (!lst)
	{
		return (NULL);
	}
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (!node)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, node);
		lst = lst->next;
	}
	return (head);
}
/*
#include <stdio.h>
void *multiply_two(void *content)
{
	int *new_value = malloc(sizeof(int));
	if (new_value)
	{
		*new_value = (*(int *)content * 2);
	}

	return (new_value);
}

void del(void *content)
{
	free(content);
}

int	main(void)
{
	t_list *start;
	int *data1 = malloc(sizeof(int));
	int *data2 = malloc(sizeof(int));
	int *data3 = malloc(sizeof(int));
	*data1 = 12; *data2 = 24; *data3 = 36;

	start = ft_lstnew(data1);
	ft_lstadd_back(&start, ft_lstnew(data2));
	ft_lstadd_back(&start, ft_lstnew(data3));

	t_list *the_new_start = ft_lstmap(start, multiply_two, del);
	t_list *current = the_new_start;

	while (current)
	{
		printf("%d\n", *(int *)current->content); current = current->next;
	}
	
	ft_lstclear(&start, del); ft_lstclear(&the_new_start, del);
	return (0);
}*/