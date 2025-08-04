/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instancer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:19:31 by furizalex         #+#    #+#             */
/*   Updated: 2025/08/01 17:19:45 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/minishell.h"

t_minishell	*minishell(void)
{
	static t_minishell	instance;

	return (&instance);
}

t_lexer	*lexers(void)
{
	static t_lexer	instance;

	return (&instance);
}