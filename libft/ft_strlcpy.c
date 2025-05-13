/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:54:54 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 15:02:01 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

strlcpy

Synopsis

#include <string.h>

size_t
strlcpy(char *dst, const char *src, size_t size); 

Description

The strlcpy() function copies up to size - 1 characters from 
the NUL-terminated string src to dst, NUL-terminating the result. 

Return Value

The strlcpy() return the total length of the string they 
tried to create
*/

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_len);
}
/*
#include <stdio.h>
int	main(void)
{
	char src[] = "Copyable String";
	char dest[20];

	size_t copied = ft_strlcpy(dest, src, sizeof(dest));

	printf("Source string: %s\n", src);
	printf("Destination string: %s\n", dest);
	printf("Total length of source: %zu\n", copied);
	return (0);
}*/
