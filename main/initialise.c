/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:16:55 by alechin           #+#    #+#             */
/*   Updated: 2025/08/20 13:53:25 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

void	init_shell_vars(t_minishell *o, t_micro *shell, t_token **tokens)
{
	t_token	*temp;

	(void)o;
	*shell = (t_micro){0};
	temp = *tokens;
	shell->id_start = (*tokens)->id;
	shell->id_end = ft_tokenlst(*tokens)->id;
	shell->length = 0;
	while (temp)
	{
		shell->length++;
		temp = temp->next;
	}
}

void	handle_execution(t_root **root, t_minishell *o, t_micro shell)
{
	o->status = recursive_tree(root, shell, &o->token, true);
	if (o->status == UNDECLARED)
	{
		if (o->root)
			o->last_status = execution(*root);
		else
			o->last_status = 1;
	}
}

char	*get_prompt(void)
{
	return ("\033[33m-- BASS AMATEUR SHELL --\033[36m\n"
		"[🐡 FISH BITES] o->\033[0m ");
}

void	initialise(int *argc, char ***argv, t_token **tokens, char **env)
{
	t_minishell	*o;

	(void)argc;
	(void)argv;
	(void)env;
	*tokens = NULL;
	o = minishell();
	o->lcl_env = NULL;
	o->last_status = 0;
	o->env = cpyenv(env);
	o->export = ft_calloc(countword(o->env) + 1, sizeof(int));
	o->root = NULL;
	o->status = UNDECLARED;
}
