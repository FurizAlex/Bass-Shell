/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:20:37 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 18:19:54 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

memchr

Synopsis

#include <string.h>

void *memchr(const void *s, int c, size_t n);

Description

The memchr() function scans the initial n bytes of the memory area
 pointed to by s for the first instance of c. 
Both c and the bytes of the memory area 
pointed to by s are interpreted as unsigned char. 

Return Value

The memchr() and memrchr() functions return a pointer to the matching byte
 or NULL if the character does not occur in the given memory area. 
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	target;

	ptr = (unsigned char *)s;
	target = (unsigned char)c;
	while (n--)
	{
		if (*ptr == target)
		{
			return ((void *)ptr);
		}
		ptr++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	*str = "Hello, World";
	char	*result = (char *)ft_memchr(str, 'o', 10);

	printf("position is at %ld\n", result - str);
	return (0);
}*/