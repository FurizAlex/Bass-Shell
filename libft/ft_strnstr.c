/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:19:55 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 15:27:46 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

strnstr

Synopsis

#include <string.h>

char *strnstr(const char *haystack, const char *needle, size_t len);

Description

The strnstr() function locates the first occurrence of the null-termi-
nated string needle in the string haystack, 
where not more than len characters are searched.
Characters that appear after a `\0' character are not searched.

Return Value

If needle is an empty string, haystack is returned; if needle occurs nowhere
in haystack, NULL is returned; otherwise a pointer to the first character of
the first occurrence of needle is returned.
*/

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t num)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < num && haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < num)
		{
			if (needle[j + 1] == '\0')
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char *haystack = "Hello, world!";
	char *needle = "world";
	char *result = ft_strnstr(haystack, needle, 13);

	if (result)
		printf("found: %s\n", result);
	else
		printf("not found\n");
	return (0);
}*/
