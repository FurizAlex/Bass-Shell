/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:28:17 by alechin           #+#    #+#             */
/*   Updated: 2025/08/07 16:43:02 by furizalex        ###   ########.fr       */
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
	t_micro		shell;

	o = minishell();
	*root = NULL;
	shell.id_start = (*tokens)->id;
	shell.id_end = ft_tokenlst(*tokens)->id;
	shell.length = 0;
	t_token *temp = *tokens;
	while (temp)
	{
		shell.length++;
		temp = temp->next;
	}
	*root = create_initial_root(tokens, &shell);
	o->root = *root;
	if (!(*root))
	{
		o->status = UNDECLARED;
		o->last_status = 1;
		return ;
	}
	(*root)->msh = o;
	o->status = recursive_tree(root, shell, tokens, true);
	if (o->status == UNDECLARED)
	{
		if (o->root)
			o->last_status = execution(*root);
		else
			o->last_status = 1;
	}
	terminate_ast(root);
}

static void	status_clearance(void)
{
	t_minishell	*o;
	t_root		*root;

	o = minishell();
	if (o->status == UNDECLARED)
		attach_exec(&root, &o->token);
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
	set_token_prev_pointers(tokens);
	o->token = tokens;
	ast = parse(tokens);
	if (ast)
	{
		o->status = UNDECLARED;
		status_clearance();
		free_ast(ast);
	}
}

void	shell_loop(void)
{
	char		*cmd;

	while (1)
	{
		cmd = readline("\033[33m-- BASS AMATEUR SHELL --\033[36m\n[🐡 FISH BITES] o->\033[0m ");
		printf("Input received: '%s'\n", cmd);
		if (!cmd)
		{
			write(1, "Exit\n", 5);
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
