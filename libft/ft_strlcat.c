/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:20:46 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 14:58:42 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

strlcat

Synopsis

#include <string.h>

size_t
strlcat(char *dst, const char *src, size_t size); 

Description

The strlcat() function appends the
NUL-terminated string src to the end of dst. 
It will append at most size - 
strlen(dst) - 1 bytes,
NUL-terminating the result. 

Return Value

strlcat() functions return the total length
of the string they tried to create
*/

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size <= dest_len)
		return (size + src_len);
	i = 0;
	while (i < size - dest_len - 1 && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
/*
#include <stdio.h>
int	main(void)
{
	char	dest[20] = "Hello, ";
	char	*src = "world";
	size_t result = ft_strlcat(dest, src, sizeof(dest));

	printf("the result of the string is %s\n", dest);
	printf("total length: %zu\n", result);
	return (0);
}*/
