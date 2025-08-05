/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:51:47 by furizalex         #+#    #+#             */
/*   Updated: 2025/07/30 15:38:35 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/parsing.h"

t_token	*ft_tokenlst(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}
