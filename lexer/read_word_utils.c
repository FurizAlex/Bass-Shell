/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_word_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:42:55 by rpadasia          #+#    #+#             */
/*   Updated: 2025/09/02 22:57:57 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_token	*return_token(char *word, bool has_expansion)
{
	t_token	*token;

	token = create_token(TOKEN_WORD, word, has_expansion);
	free(word);
	return (token);
}
