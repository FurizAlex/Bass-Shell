/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:42:44 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/29 21:54:53 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/*Gathers consecutive WORD tokens into NULL-terminated string array*/
char	**collect_command_args(t_parser *parser, int *arg_counter)
{
	char	**args;
	int		count;

	args = malloc(sizeof(char *) * 64);
	count = 0;
	while (parser->current_token
		&& parser->current_token->type == TOKEN_WORD)
	{
		args[count] = ft_strdup(parser->current_token->value);
		count++;
		advance_parser(parser);
	}
	args[count] = NULL;
	*arg_counter = count;
	return (args);
}
