/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:30:35 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 14:34:18 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

split

char **ft_split(char const *s, char c);

Description

Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a space. The array must end
with a NULL pointer.

Return Value

The array of new strings resulting from the split.
NULL if the allocation fails.
*/

#include "libft.h"

static void	*free_all(char **result, int z)
{
	int	i;

	i = 0;
	while (i < z)
		free(result[i++]);
	free(result);
	return (NULL);
}

static int	ft_count_substrings(char const *s, char c)
{
	int	count;
	int	in_substring;

	count = 0;
	in_substring = 0;
	while (*s)
	{
		if (*s != c && in_substring == 0)
		{
			in_substring = 1;
			count++;
		}
		else if (*s == c)
		{
			in_substring = 0;
		}
		s++;
	}
	return (count);
}

static char	*ft_strlen_until_char(const char *s, char c, int *i)
{
	char	*ptr;
	int		size;
	int		j;
	int		a;

	size = 0;
	j = *i;
	a = 0;
	while (s[j] && s[j] != c)
	{
		size++;
		j++;
	}
	ptr = malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (NULL);
	while (*i < j)
	{
		ptr[a++] = s[*i];
		*i += 1;
	}
	ptr[a] = '\0';
	return (ptr);
}

static char	**split_words(char **result, char const *s, char c)
{
	int	i;
	int	a;

	i = 0;
	a = -1;
	while (s[i])
	{
		if (s[i] != c)
		{
			result[++a] = ft_strlen_until_char(s, c, &i);
			if (!result[a])
				return (free_all(result, a));
		}
		else
			i++;
	}
	result[++a] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		size;

	if (!s)
		return (NULL);
	size = ft_count_substrings(s, c);
	result = malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	if (!split_words(result, s, c))
	{
		free(result);
		return (NULL);
	}
	return (result);
}
/*
#include <stdio.h>
int	main()
{
	char *str = "Hello world this is split";
	char **result = ft_split(str, ' ');
	int i = 0;

	while (result[i] != NULL)
	{
		printf("%s\n", result[i]);
		i++;
	}
	while (result[i] != NULL)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}*/
