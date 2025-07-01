/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:36:11 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 15:57:47 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Name
bzero - write zero-valued bytes

Synopsis

#include <strings.h>

void bzero(void *s, size_t n);

Description
The bzero() function sets the first n bytes of the area starting at s to zero.

Return Value
None. 
*/

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = s;
	while (n--)
	{
		*ptr++ = 0;
	}
}
/*
#include <stdio.h>
int	main(void)
{
	char	str[16] = "1010101010101010";

	printf("Before: %s\n", str);
	ft_bzero(str + 5, 10);
	printf("After: %s\n", str);
}*/
