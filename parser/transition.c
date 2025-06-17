/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <rpadasia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:42:44 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/17 16:48:48 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char	**collect_command_args(t_parser *parser, int *arg_counter)
{
	char	**args;
	int		count;

	args = malloc(sizeof(char *) * 64);
	count = 0;
	while (parser->current_token
		&& parser->current_token->type == TOKEN_WORD)
	{
		args[count] = ft_strdup(parser->parser->current_token->value);
		count++;
		advance_parser(parser);
	}
	args[count] = NULL;
	*arg_count = count;
	return (args);
}
