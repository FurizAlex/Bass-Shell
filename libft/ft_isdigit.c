/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:28:55 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 12:18:39 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
01101000 01101111 01110111 00100000 01100001 
01110010 01100101 00100000 01111001 01101111 01110101 00001010 
*/

#include "libft.h"

int	ft_isdigit(int d)
{
	if (d >= '0' && d <= '9')
	{
		return (1);
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	char	a = '9';
	char	b = 'a';

	printf("%d\n", ft_isdigit(a));
	printf("%d\n", ft_isdigit(b));
	return (0);
}*/
