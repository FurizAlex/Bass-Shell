/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:30:15 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 16:17:04 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name; Calloc

Synopsis

#include <stdlib.h>

void *calloc(size_t nmemb, size_t size);

Description

The calloc() function allocates memory for an array of nmemb elements
of size bytes each and returns a pointer to the allocated memory. 
The memory is set to zero. If nmemb or size is 0, 
then calloc() returns either NULL, 
or a unique pointer value that can later be successfully passed to free().

Return Value

calloc() functions return a pointer to the allocated memory
 that is suitably aligned for any kind of variable. 
*/

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	size_t			bytes;

	if (nmemb == 0 || size == 0)
	{
		return (malloc(0));
	}
	if (nmemb > (size_t)(-1) / size)
	{
		return (NULL);
	}
	bytes = nmemb * size;
	ptr = malloc(bytes);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_memset(ptr, 0, bytes);
	return (ptr);
}
/*
#include <stdio.h>
int	main(void)
{
	int	*arr = (int *)ft_calloc(0, sizeof(int));
	if (arr == NULL)
	{
		printf("memory alloc failed\n");
		return (1);
	}
	int i = 0;
	while (i < 5)
	{
		printf("%d\n", arr[i]);
		i++;
	}
	free(arr);
	return (0);
}*/