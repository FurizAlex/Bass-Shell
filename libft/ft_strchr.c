/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:04:02 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 14:55:58 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

strchr

char *strchr(const char *s, int c);

Description

The strchr() function returns a pointer to the first
occurrence of the character c in the string s. 

Return Value

The strchr() functions return a pointer to the matched character 
or NULL if the character is not found.
 The terminating null byte is considered part of the string, 
 so that if c is specified as aq\0aq,
  these functions return a pointer to the terminator. 
*/

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	if (c == '\0')
	{
		return ((char *)str + ft_strlen(str));
	}
	while (*str != '\0')
	{
		if (*str == (char)c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*str = "Hello world";
	char	*c = ft_strchr(str, 'o');
	if (!c)
	{
		printf("NULL");
		return (0);
	}
	printf("%s\n", c);
	return (0);
}*/
