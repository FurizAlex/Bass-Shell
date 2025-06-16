/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:30:19 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 15:02:49 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

strlen

Synopsis

#include <string.h>

size_t strlen(const char *s);

Description

The strlen() function calculates the length of the string s,
 excluding the terminating null byte

Return Value

The strlen() function returns the number of bytes in the string s.
*/

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}
/*
#include <stdio.h>
int	main(void)
{
	char *s = "Thisshouldbe19words";

	printf("%zu\n", ft_strlen(s));
	return (0);
}*/
