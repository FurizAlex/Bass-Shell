/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:02:29 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 15:56:17 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

tolower

Synopsis

#include <ctype.h>

int tolower(int c);

Description

tolower() converts the letter c to lower case,
if possible. 

Return Value

The value returned is that of the converted letter,
or c if the conversion was not possible. 
*/

#include "libft.h"

int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
	{
		return (c + 'a' - 'A');
	}
	return (c);
}
/*
#include <stdio.h>
int	main()
{
	char	str[] = "HELLO, WORLD";
	int	i = 0;

	while (str[i] != '\0')
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	printf("Converted string %s\n", str);
	return (0);
}*/
