/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:28:55 by rpadasia          #+#    #+#             */
/*   Updated: 2025/07/02 11:11:38 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/*goes through line, returning false when it hits a non-whitespace
character*/
static bool	is_empty_input(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	process_input(char *input)
{
	t_token		*tokens;
	t_ast_node	*ast;

	tokens = tokenize(input);
	if (!tokens)
		return ;
	ast = parse(tokens);
	if (ast)
	{
		free_ast(ast);
	}
	free_tokens(tokens);
}
