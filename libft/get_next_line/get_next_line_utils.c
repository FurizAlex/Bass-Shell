/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:16:07 by alechin           #+#    #+#             */
/*   Updated: 2024/12/30 15:06:38 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *len)
{
	size_t	length;

	length = 0;
	if (!len)
		return (0);
	while (len[length])
	{
		length++;
	}
	return (length);
}

char	*gnl_strchr(char *str, int c)
{
	if (!str)
		return (NULL);
	if (c == '\0')
		return ((char *)&str[gnl_strlen(str)]);
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	return (NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	if (s1)
		while (s1[++i])
			str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[gnl_strlen(s1) + gnl_strlen(s2)] = '\0';
	free(s1);
	return (str);
}
