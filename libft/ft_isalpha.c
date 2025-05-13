/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:20:54 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 12:16:55 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
no-alt-text
*/

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	char a = '9';
	char b = 'a';

	printf("%d\n", ft_isalpha(a));
	printf("%d\n", ft_isalpha(n));
	return (0);
}*/