/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:28:17 by alechin           #+#    #+#             */
/*   Updated: 2025/09/02 23:00:38 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "execution.h"
#include "parsing.h"

/*goes through line, returning false when it hits a non-whitespace
character*/

extern int	g_signal;

void	execute_direct_ast(t_token **tokens)
{
	t_ast_node	*ast;
	t_minishell	*msh;

	msh = minishell();
	ast = parse(*tokens);
	if (!ast)
	{
		msh->last_status = 1;
		return ;
	}
	msh->last_status = execute_ast(ast);
	free_ast(ast);
}

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

void	process_input_new(char *input)
{
	t_token		*tokens;
	t_minishell	*msh;

	msh = minishell();
	process_signal_state(msh);
	tokens = tokenize(input);
	if (!tokens)
		return ;
	set_token_prev_pointers(tokens);
	msh->token = tokens;
	execute_direct_ast(&tokens);
	free_tokens(tokens);
	msh->token = NULL;
	reset_signals_interactive();
}

void	shell_loop(void)
{
	char		*cmd;

	while (1)
	{
		reset_shell_state();
		cmd = readline("\033[33m-BASS SHELL-\033[36m\n[🐡FISHBITES]o->\033[0m ");
		if (handle_eof_input(cmd))
		{
			cleanup_history();
			break ;
		}
		if (!is_empty_input(cmd))
		{
			add_history(cmd);
			process_input_new(cmd);
		}
		free(cmd);
	}
}
