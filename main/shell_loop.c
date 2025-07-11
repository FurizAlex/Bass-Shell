/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:28:17 by alechin           #+#    #+#             */
/*   Updated: 2025/07/11 11:42:15 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "execution.h"
#include "parsing.h"

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
		execution((t_root *)ast);
		free_ast(ast);
	}
	free_tokens(tokens);
}

void	shell_loop(void)
{
	char	*cmd;

	while (1)
	{
		cmd = readline("\033[33m-- BASS AMATEUR SHELL --\033[36m\n[🐡 FISH BITES] o->\033[0m ");
		if (!cmd)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (!is_empty_input(cmd))
		{
			add_history(cmd);
			process_input(cmd);
		}
		free(cmd);
	}
}
