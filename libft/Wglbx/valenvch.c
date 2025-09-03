/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valenvch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:18 by alechin           #+#    #+#             */
/*   Updated: 2025/07/10 12:57:45 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This is basically to check if its a valid environment character */

#include "wglbx.h"

int	valid_env_ch(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}
