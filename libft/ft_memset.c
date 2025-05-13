/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:31:54 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 14:18:26 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

memset

Synopsis

#include <string.h>

void *memset(void *s, int c, size_t n);

Description

The memset() function fills the first n bytes of 
the memory area pointed to by s with the constant byte c. 

Return Value

The memset() function returns a pointer to the memory area s
*/

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n--)
	{
		*ptr = (unsigned char)c;
		ptr++;
	}
	return (s);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*d;
	int	*d2;
	int	i;

	i = 0;
	d = malloc(5);
	d2 = malloc(4*5);
	d[4] = '\0';
	printf("%s\n", (char *)ft_memset(d, 'h', 10));
	return (0);
}*/