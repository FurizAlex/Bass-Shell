/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:42:08 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 16:09:45 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

memmove

Synopsis

#include <string.h>

void *memmove(void *dest, const void *src, size_t n);

Description

The memmove() function copies n bytes from memory area src to memory area dest. 
The memory areas may overlap: 
copying takes place as though the bytes in src are first copied into a
temporary array that does not overlap src or dest, 
and the bytes are then copied from the temporary array to dest.

Return Value

The memmove() function returns a pointer to dest. 
*/

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dest;
	s = src;
	if (d == s)
	{
		return (dest);
	}
	if (s < d && d < s + n)
	{
		s += n;
		d += n;
		while (n--)
			*(--d) = *(--s);
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
	char str[] = "Hello World";
	
	printf("Original string: %s\n", str);
	ft_memmove(str + 6, str + 7, 5);
	printf("String after moving: %s\n", str);
}*/