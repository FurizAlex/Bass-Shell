/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupnxtra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:36:18 by alechin           #+#    #+#             */
/*   Updated: 2025/07/10 12:44:15 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wglbx.h"

char	*dupnxtra(char *str, size_t n)
{
	char	*dup;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, str, n + 1);
	return (dup);
}
