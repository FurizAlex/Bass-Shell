/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:38:36 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 14:43:21 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

striteri

Synopsis

#include <string.h>

void ft_striteri(char *s, void (*f)(unsigned int,
char*));s

Description

Applies the function ’f’ on each character of
the string passed as argument, passing its index
as first argument. Each character is passed by
address to ’f’ to be modified if necessary.

Return Value

it doesn't
*/

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
	{
		return ;
	}
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
#include <stdio.h>
void	uppercase(unsigned int i, char *c)
{
	if (*c >= 'a' && *c <= 'z')
		*c = *c - 32;
}

int	main(void)
{
	char str[] = "hello";
	ft_striteri(str, uppercase);
	printf("modified: %s\n", str);
	return (0);
}*/
