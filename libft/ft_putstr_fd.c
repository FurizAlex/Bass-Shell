/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:06:08 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 14:28:17 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

putstr_fd

void ft_putstr_fd(char *s, int fd);

Description

Outputs the string ’s’ to the given file
descriptor.

Return Value

It doesn't
*/

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
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
}
/*
int	main(void)
{
	ft_putstr_fd("Hello world", 1);
}*/
