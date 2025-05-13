/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:42 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 12:16:37 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DABIDABIDOO
*/

#include "libft.h"

int	ft_isalnum(int c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}

/*
#include <stdio.h>
int	main(void)
{
	char	a = 'a';
	char	b = '@';
	char	c = '5';

	printf("%d\n", ft_isalnum(a));
	printf("%d\n", ft_isalnum(b));
	printf("%d\n", ft_isalnum(c));
	return (0);
}*/
