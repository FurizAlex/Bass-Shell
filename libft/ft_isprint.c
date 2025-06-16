/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:25:21 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 12:24:00 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
-.-- .- / -.- -. --- .-- / 
-- --- .-. ... . / -.-. --- -.. . ..--..
*/

int	ft_isprint(int c)
{
	return ((c >= 32 && c <= 126));
}
/*
#include <ctype.h>
#include <stdio.h>
int	main(void)
{
	char ch = 'a';

	if (isprint(ch))
	{
		printf("%c is printable\n", ch);
	}
	else
	{
		printf("%c is not printable\n", ch);
	}
	return (0);
}*/
