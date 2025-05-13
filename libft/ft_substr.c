/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:09:43 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 15:54:05 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

substr

char *ft_substr(char const *s, unsigned int start,
size_t len);

Description

Allocates (with malloc(3)) and returns a substring
from the string ’s’.
The substring begins at index ’start’ and is of
maximum size ’len’

Return Value

The substring.
NULL if the allocation fails.
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
	{
		return (NULL);
	}
	if (start >= ft_strlen(s))
	{
		substr = (char *)malloc(1);
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	ft_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}
/*
#include <stdio.h>
int	main(void)
{
	char *substr = ft_substr("Hello, world!", 7, 5);
	if (substr)
	{
		printf("%s\n", substr);
		free(substr);
	}
	return (0);
}*/
