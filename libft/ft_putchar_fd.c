/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:39:41 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 14:20:35 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

putchar_fd

void ft_putstr_fd(char *s, int fd);

Description

Outputs the string ’s’ to the given file
descriptor.

Return Value

It doesn't
*/

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
int	main()
{
	ft_putchar_fd('a', 1);
}*/
