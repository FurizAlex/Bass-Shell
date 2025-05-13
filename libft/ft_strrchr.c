/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:31:31 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 15:38:07 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

strrchr

Synopsis

#include <string.h>

char *strrchr(const char *s, int c);

Description

The strrchr() function returns a pointer to the last
occurrence of the character c in the string s. 

Return Value

The strrchr() functions return a pointer to the matched character 
or NULL if the character is not found. 
The terminating null byte is considered part of the string,
these functions return a pointer to the terminator. 
*/

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*last_occ;

	last_occ = NULL;
	while (*str != '\0')
	{
		if (*str == (char)c)
		{
			last_occ = (char *)str;
		}
		str++;
	}
	if (*str == (char)c)
	{
		last_occ = (char *)str;
	}
	return (last_occ);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*str = "Hello World";
	char	*occ = ft_strrchr(str, 'o');
	if (!occ)
	{
		printf("NULL");
		return (0);
	}
	printf("%s\n", occ);
	return (0);
}*/
