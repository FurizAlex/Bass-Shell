/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:37:57 by alechin           #+#    #+#             */
/*   Updated: 2025/03/31 09:47:56 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

strdup

Synopsis

#include <string.h>

char *strdup(const char *s);

Description

The strdup() function returns a pointer to 
a new string which is a duplicate of the string s.
Memory for the new string is obtained with
 malloc(3), and can be freed with free(3). 

Return Value

The strdup() function returns a pointer to the duplicated string,
or NULL if insufficient memory was available. 
*/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	n;
	size_t	i;
	char	*dup;

	n = 0;
	while (s[n] != '\0')
	{
		n++;
	}
	dup = (char *)malloc(n + 1);
	if (dup == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/*
#include <stdio.h>
int	main()
{
	char *str = "Hello, world!";
	char *copy = ft_strdup(str);

	printf("copy: %s\n", copy);
	free(copy);
	return (0);
}*/
