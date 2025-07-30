/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:28:17 by alechin           #+#    #+#             */
/*   Updated: 2025/07/28 09:37:55 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "execution.h"
#include "parsing.h"

/*goes through line, returning false when it hits a non-whitespace
character*/

static void	attach_exec(t_root **root, t_token **tokens)
{
	t_minishell	*o;

	o = minishell();
	o->status = ast(root, tokens);
	o->token = *tokens;
	o->root = *root;
	if (o->status == UNDECLARED)
		o->last_status = execution(*root);
	terminate_ast(root);
}

static void	status_clearance(void)
{
	t_minishell	*o;
	t_root		*root;
	t_token		*tokens;

	o = minishell();
	if (o->status == UNDECLARED)
		attach_exec(&root, &tokens);
	if (o->status == INTERACTIVE)
		o->last_status = 130;
	if (o->status == EOFS)
		return ;
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

static void	process_input(char *input)
{
	t_token		*tokens;
	t_ast_node	*ast;
	t_minishell	*o;

	o = minishell();
	tokens = tokenize(input);
	if (!tokens)
		return ;
	ast = parse(tokens);
	if (ast)
	{
		o->status = UNDECLARED;
		status_clearance();
		free_ast(ast);
	}
	free_tokens(tokens);
}

void	shell_loop(void)
{
	char		*cmd;

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
