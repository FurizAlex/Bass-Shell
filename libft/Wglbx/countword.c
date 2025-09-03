/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countword.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:22:42 by alechin           #+#    #+#             */
/*   Updated: 2025/08/11 16:09:34 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wglbx.h"

int	countword(char **wgstr_of_array)
{
	int	i;

	i = 0;
	while (wgstr_of_array[i] != NULL)
		i++;
	return (i);
}
