/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:52:56 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 15:57:20 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

toupper

Synopsis

#include <ctype.h>

int toupper(int c);

Description

toupper() converts the letter c to upper case,
if possible. 

Return Value

The value returned is that of the converted letter,
or c if the conversion was not possible. 
*/

#include "libft.h"

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
	{
		return (c - 'a' + 'A');
	}
	return (c);
}
/*
#include <stdio.h>
int	main()
{
	char	str[] = "Hello, World";
	int	i = 0;

	while (str[i] != '\0')
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	printf("Converted string %s\n",str);
	return (0);
}*/
