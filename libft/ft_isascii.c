/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:20:37 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 12:17:31 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
ASCII ART
*/

#include "libft.h"

int	ft_isascii(int c)
{
	return ((c >= 0 && c <= 127));
}
/*
#include <stdio.h>
int	main(void)
{
	char	a = 'a';
	char	b = '1';
	int	c = 128;

	printf("%d\n", ft_isascii(a));
	printf("%d\n", ft_isascii(b));
	printf("%d\n", ft_isascii(c));
	return (0);
}*/
