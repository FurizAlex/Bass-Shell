/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncomp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:01:56 by alechin           #+#    #+#             */
/*   Updated: 2025/06/18 13:57:37 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wglbx.h"

int	ncomp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i++ < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
