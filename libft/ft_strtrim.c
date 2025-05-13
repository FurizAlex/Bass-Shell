/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:20:39 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 15:53:17 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

strtrim

char *ft_strtrim(char const *s1, char const *set);

Description

Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.

Return Value

The trimmed string.
NULL if the allocation fails
*/

#include "libft.h"

static int	ft_is_trim_char(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
		{
			return (1);
		}
		set++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_is_trim_char(s1[start], set))
		start++;
	while (ft_is_trim_char(s1[end], set) && end > start)
		end--;
	ptr = malloc(end - start + 2);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1 + start, end - start + 1);
	ptr[end - start + 1] = '\0';
	return (ptr);
}
/*
#include <stdio.h>
int	main(void)
{
	char *str = "	\t\nHello, World!	\n\t	";
	char *set = "	\t\n";
	char *trim_str = ft_strtrim(str, set);

	printf("trimmed: %s\n", trim_str);
	free(trim_str);
	return (0);
}*/
