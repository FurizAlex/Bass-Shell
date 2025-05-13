/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:45:18 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 15:19:23 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

strncmp

Synopsis

#include <string.h>

int strncmp(const char *s1, const char *s2, size_t n);

Description

The strcmp() function compares the two strings s1 and s2.
It returns an integer less than, equal to,
or greater than zero if s1 is found, respectively,
to be less than, to match, or be greater than s2. 

Return Value

The strncmp() functions return an integer less than, 
equal to, or greater than zero if s1 (or the first n bytes thereof)
is found, respectively, to be less than, 
to match, or be greater than s2. 
*/

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		i++;
	}
	if (i < n)
	{
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	char *str = "Hello";
	char *a2str = "Helyo";
	char *a3str = "World";

	printf("%d\n", ft_strncmp(str, a2str, 2));
	printf("%d\n", ft_strncmp(a3str, a2str, 6));
	printf("%d\n", ft_strncmp(str, a2str, 6));
	return (0);
}*/
