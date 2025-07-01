/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:03:33 by alechin           #+#    #+#             */
/*   Updated: 2025/03/10 09:59:02 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

atoi

Synopsis

#include <stdlib.h>

int atoi(const char *nptr);

Description

The atoi() function converts the initial portion of the string 
pointed to by nptr to int. The behavior is the same as

Return Value

The converted value
*/

#include "libft.h"

long int	ft_atoi(const char *str)
{
	long int	num;
	int			neg;
	int			i;

	num = 0;
	neg = 1;
	i = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if ((neg == 1 && num > INT_MAX) || (neg == -1 && neg * num < INT_MIN))
		return (0);
	return (num * neg);
}
/*
#include <stdio.h>
int	main()
{
	char	*str = "12345";
	char	*a2str = " -6789";
	char	*a3str = "42abc";
	int	num = ft_atoi(str);
	int	a2num = ft_atoi(a2str);
	int	a3num = ft_atoi(a3str);

	printf("first str: %s to int: %d\n", str, num);
	printf("second str: %s to int: %d\n", a2str, a2num);
	printf("third str: %s to int: %d\n", a3str, a3num);
	return (0);
}*/
