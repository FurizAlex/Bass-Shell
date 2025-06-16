/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:38:10 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 14:18:47 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

memcpy

Synopsis

#include <string.h>

void *memcpy(void *dest, const void *src, size_t n);

Description

he memcpy() function copies n bytes from memory area src to memory area dest. 
The memory areas must not overlap. 
Use memmove(3) if the memory areas do overlap.

Return Value

The memcpy() function returns a pointer to dest. 
*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dest;
	s = src;
	while (n--)
	{
		*d = *s;
		d++;
		s++;
	}
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*dest = malloc(11);
	char	*src = "Hello World";

	ft_memcpy(dest, src, 11);
	printf("%s\n", src);
	printf("%s\n", dest);
	return (0);
}*/