/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:56:14 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 14:21:05 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

putchar_fd

void ft_putendl_fd(char *s, int fd);

Description

Outputs the string ’s’ to the given file descriptor
followed by a newline

Return Value

It doesn't
*/

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s == NULL)
	{
		return ;
	}
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}
/*
int	main(void)
{
	ft_putendl_fd("Hello", 1);
}*/
